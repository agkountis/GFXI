#ifndef BLADE_LIB_NCF_H_
#define BLADE_LIB_NCF_H_

#include <string>
#include <map>
#include "declspec.h"

namespace Blade
{
	class NCF_DECLSPEC NCF
	{
	private:
		std::string m_Name; // Node name.

		mutable std::map<std::string, NCF*> m_Groups; // Sub-node map.

		mutable std::map<std::string, std::string> m_Symbols; // Symbol map.

		std::string m_Filepath; // Source path.

		unsigned int m_Level; // Node level.

		void Release();

		void ExpandSymbol(std::map<std::string, std::string>& symbols, std::string& s);

	public:
		NCF();
		~NCF();

		void SetSource(const char* file);
		const char* GetSource() const;

		void Purge();

		/* RETURN CODES:
		** 0 : Everything went well.
		** 1 : Not an ASCII file.
		** 2 : File I/O error.
		** 3 : Syntax error.
		** 4 : Unbalanced groups.
		*/
		int Parse();

		/* RETURN CODES:
		** 0 : Everything went well.
		** 1 : File I/O error.
		*/
		int Dump(const char* file, int create = 1) const;

		bool QueryProperty(const char* name) const;

		bool QueryGroup(const char* name) const;

		unsigned int CountProperties() const;

		unsigned int CountGroups() const;

		void SetProperty(const char* name, const char* value);

		const char* GetPropertyByName(const char* name) const;

		const char* GetPropertyByIndex(unsigned int index) const;

		const char* GetPropertyNameByIndex(unsigned int index) const;

		NCF* GetGroupByName(const char* name) const;

		NCF* GetGroupByIndex(unsigned int index) const;

		const char* GetName() const;

		NCF(const NCF&) = delete;
		NCF& operator =(const NCF&) = delete;
	};
}

#endif //BLADE_LIB_NCF_H_
