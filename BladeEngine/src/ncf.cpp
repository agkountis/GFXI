#include <cstdio>
#include <fstream>
#include <list>
#include "util.h"
#include "ncf.h"

namespace Blade
{
	NCF::NCF()
		: m_Level(0)
	{}

	NCF::~NCF()
	{
		Release();
	}

	void NCF::SetSource(const char *file)
	{
		m_Filepath = file;
	}

	const char* NCF::GetSource() const
	{
		return m_Filepath.c_str();
	}

	void NCF::Purge()
	{
		Release();
	}

	void NCF::Release()
	{
		std::map<std::string, NCF*>::iterator it = m_Groups.begin();
		std::map<std::string, NCF*>::iterator et = m_Groups.end();

		for (; it != et; ++it)
		{
			delete it->second;

#ifdef CONFIG_DEBUG
			printf("NCF parser: [-node: %p]\n", (void *)it->second);
#endif /* CONFIG_DEBUG */
		}

		m_Groups.clear();
		m_Symbols.clear();
	}

	int NCF::Parse()
	{
		// Sanity check
		{
			int c;
			std::ifstream in(m_Filepath.c_str());

			if (!in.good())
				return 2;

			while ((c = in.get()) != EOF && c <= 127);

			in.close();

			if (c != EOF)
				return 1;
		}

		// Stack of groups for parsing.
		std::list<NCF*> group_stack;

		group_stack.push_front(this);

		// Process file.
		std::fstream in(m_Filepath.c_str(), std::ios::in);

		if (!in.good()) return 2;

		int linep = 0;
		int sectionp = 0;

		std::string input;
		while (getline(in, input))
		{
			linep++;

			std::string line, comment;

			Util::String::split(input, line, comment, '#'); // Strip comments.
			Util::String::trim(line); // Trim spaces and unused characters.

			if (!line.length())
			{
				// Empty line - do nothing.
			}
			else if (line.length() > 2 && (line.find('=') != std::string::npos))
			{
				// Get the identifier and its value.
				std::string name, value;
				Util::String::split(line, name, value, '=');

				// Trim the name and its value from unused characters and spaces.
				Util::String::trim(name);
				Util::String::trim(value);

				// If this is a section start.
				if (value == "{")
				{
					sectionp++;

					std::map<std::string, NCF*>::iterator it = group_stack.front()->m_Groups.find(name);

					// Check whether the group name already exists and create a new node, if needed.
					if (it == group_stack.front()->m_Groups.end())
					{
						NCF *new_group = new NCF();
						new_group->m_Level = group_stack.front()->m_Level + 1;
						group_stack.front()->m_Groups[name] = new_group;
						new_group->m_Name = name;

#ifdef CONFIG_DEBUG
						printf("NCF parser: [+node: %p]\n", (void *)new_group);
#endif /* CONFIG_DEBUG */
					}

					// Make it the active node.
					group_stack.push_front(group_stack.front()->m_Groups[name]);
				}
				// If this is a regular assignment.
				else
				{
					std::list<NCF*>::reverse_iterator end = group_stack.rend();
					for (std::list<NCF*>::reverse_iterator it = group_stack.rbegin(); it != end; ++it) {
						(*it)->ExpandSymbol(m_Symbols, value);
					}

					group_stack.front()->m_Symbols[name] = value;
				}
			}
			// If this is a section end.
			else if ((line.length() == 1) && (line.find('}') != std::string::npos))
			{
				--sectionp;

				// Check for unbalanced sections.
				if (sectionp < 0)
				{
					fprintf(stderr, "Syntax error: Unbalanced sections at line: %i.\n", linep);
					return 1;
				}

				group_stack.pop_front();
			}
			else if ((line.length() > 1) && (line.find('%') != std::string::npos))
			{
				// get the identifier and its value.
				std::string com;
				std::string value;
				Util::String::split(line, com, value, ' ');
				// Trim the com and its value from unused characters and spaces.
				Util::String::trim(com);
				Util::String::trim(value);

				if (!com.compare("%include"))
				{
					std::string base, file;
					// Extract base path and file name of the active script.
					Util::String::path_comp(m_Filepath, base, file);

					// Append the inclusion value to the base.
					base.append(value);

#ifdef CONFIG_DEBUG
					printf("NCF inline %s\n", base.c_str());
#endif /* CONFIG_DEBUG */

					group_stack.front()->m_Filepath = base;
					group_stack.front()->Parse();
				}
				else
				{
#ifdef CONFIG_DEBUG
					printf("Syntax error: Invalid modifier [ %s ] at line:%i\n", com.c_str(), linep);
#endif /* CONFIG_DEBUG */
				}
			}
			else
			{
				fprintf(stderr, "Syntax error: Invalid entry at line: %i\n", linep);
				return 3;
			}
		}

		in.close();

		// Check for unbalanced sections.
		if (sectionp)
		{
#ifdef CONFIG_DEBUG
			fprint("Syntax error: Final unbalanced sections [ %i ].\n", linep);
#endif /* CONFIG_DEBUG */
			return 4;
		}

		return 0;
	}

	void NCF::ExpandSymbol(std::map<std::string, std::string> &symbols, std::string &s)
	{
		if (s.empty()
			|| s.length() < 3
			|| s.find_first_of('<') == s.npos
			|| s.find_first_of('<') == s.find_last_of('>'))
			return; // Nothing to expand, so return.

		std::string source = s;

		do {
			std::string search;

			// Extract reference.
			Util::String::extract(source, search, '<', '>');

			// If there is no valid pattern, return.
			if (search.length() < 3) return;

			// Purify string.
			std::string psearch = search.substr(1, search.length() - 2);

			// Try to match.
			std::map<std::string, std::string>::iterator end = symbols.end();
			for (std::map<std::string, std::string>::iterator it = symbols.begin(); it != end; ++it) {
#ifdef CONFIG_DEBUG
				printf("NCF parser: %s == %s ?\n", search.c_str(), it->first.c_str());
#endif /* CONFIG_DEBUG */

				size_t pos = psearch.compare(it->first);
				if (!pos)
				{
					Util::String::replace_first_of(s, search, it->second);
#ifdef CONFIG_DEBUG
					printf("NCF parser: Matched! %s\n", s.c_str());
#endif /* CONFIG_DEBUG */
				}
			}
		} while (1);
	}

	const char* NCF::GetPropertyByName(const char *name) const
	{
		std::map<std::string, std::string>::iterator it = m_Symbols.find(name);
		return  it == m_Symbols.end()
			? nullptr
			: it->second.c_str();
	}

	const char* NCF::GetPropertyByIndex(unsigned int index) const
	{
		if (CountProperties() == 0) return nullptr;

		std::map<std::string, std::string>::iterator it = m_Symbols.begin();
		std::map<std::string, std::string>::iterator et = m_Symbols.end();
		for (unsigned int i = 0; (it != et) && (index != i++); ++it);
		return it->second.c_str();
	}

	const char* NCF::GetPropertyNameByIndex(unsigned int index) const
	{
		if (CountProperties() == 0) return nullptr;

		std::map<std::string, std::string>::iterator it = m_Symbols.begin();
		std::map<std::string, std::string>::iterator et = m_Symbols.end();
		for (unsigned int i = 0; (it != et) && (index != i++); ++it);
		return it->first.c_str();
	}

	void NCF::SetProperty(const char *name, const char *value)
	{
		m_Symbols[name] = value;
	}

	NCF* NCF::GetGroupByName(const char *name) const
	{
		std::map<std::string, NCF* >::iterator it = m_Groups.find(name);

		// If the requested key doesn't exist then we create it.
		if (it == m_Groups.end())
		{
			m_Groups[name] = new NCF();
			m_Groups[name]->m_Level = m_Level + 1;

#ifdef CONFIG_DEBUG
			printf("NCF parser: [!node: %p]\n", (void *)m_Groups[name]);
#endif /* CONFIG_DEBUG */
		}

		return m_Groups[name];
	}

	NCF* NCF::GetGroupByIndex(unsigned int index) const
	{
		if (CountGroups() == 0) return nullptr;

		std::map<std::string, NCF*>::iterator it = m_Groups.begin();
		std::map<std::string, NCF*>::iterator et = m_Groups.end();
		for (unsigned int i = 0; (it != et) && (index != i++); ++it);
		return it->second;
	}

	unsigned int NCF::CountGroups() const
	{
		return m_Groups.size();
	}

	unsigned int NCF::CountProperties() const
	{
		return m_Symbols.size();
	}

	bool NCF::QueryProperty(const char* name) const
	{
		return m_Symbols.find(name) != m_Symbols.end();
	}

	bool NCF::QueryGroup(const char* name) const
	{
		return m_Groups.find(name) != m_Groups.end();
	}

	const char *NCF::GetName() const
	{
		return m_Name.c_str();
	}
}
