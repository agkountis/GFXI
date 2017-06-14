#include <stdlib.h>
#include <string.h>
#include "cfg.h"

#ifndef _MSC_VER
#include <alloca.h>
#else
#include <memory.h>
#endif

namespace Blade
{
	ConfigFile::ConfigFile()
		: m_Ncf{ nullptr },
		  m_OwnNcf{ false },
		  m_Valid{ false }
	{
	}

	ConfigFile::ConfigFile(const char* fname)
		: m_Ncf{ nullptr },
		m_OwnNcf{ false },
		m_Valid{ false }
	{
		Open(fname);
	}

	ConfigFile::~ConfigFile()
	{
		if (m_Ncf && m_OwnNcf)
			delete m_Ncf;
	}

	bool ConfigFile::Open(const char* fname)
	{
		m_Ncf = new NCF;
		m_OwnNcf = true;
		m_Ncf->SetSource(fname);
		if (m_Ncf->Parse() != 0)
		{
			m_Valid = false;
			return false;
		}

		m_Valid = true;
		return true;
	}

	bool ConfigFile::IsOpen() const
	{
		return m_Valid;
	}

	ConfigEntry ConfigFile::Get(const char* optname) const
	{
		if (!m_Valid)
		{
			return ConfigEntry();
		}

		char* path = static_cast<char*>(alloca(strlen(optname) + 1));
		strcpy(path, optname);

		const NCF* node = m_Ncf;

		char* dot;
		while (node && (dot = strchr(path, '.')))
		{
			*dot = 0;
			node = node->GetGroupByName(path);
			path = dot + 1;
		}

		if (!path || !node || !node->QueryProperty(path))
		{
			return ConfigEntry();
		}

		return ConfigEntry(path, node->GetPropertyByName(path));
	}


	std::list<ConfigEntry> ConfigFile::GetAll(const char* groupname) const
	{
		std::list<ConfigEntry> res;
		if (!m_Valid)
		{
			return res;
		}

		char* path = static_cast<char*>(alloca(strlen(groupname) + 1));
		strcpy(path, groupname);

		const NCF* node = m_Ncf;

		char* dot;
		while (node && (dot = strchr(path, '.')))
		{
			*dot = 0;
			node = node->GetGroupByName(path);
			path = dot + 1;
		}

		if (!path || !node || !(node = node->GetGroupByName(path)))
		{
			return res;
		}

		for (unsigned int i = 0; i < node->CountProperties(); i++)
		{
			ConfigEntry ent(node->GetPropertyNameByIndex(i), node->GetPropertyByIndex(i));
			res.push_back(ent);
		}
		return res;
	}


	const char* ConfigFile::GetString(const char* optname, const char* def) const
	{
		ConfigEntry ent = Get(optname);
		if (ent.IsValid())
		{
			return ent.GetValueString();
		}
		return def;
	}

	int ConfigFile::GetInteger(const char* optname, int def) const
	{
		ConfigEntry ent = Get(optname);
		if (ent.IsValid())
		{
			return ent.GetValueInt();
		}
		return def;
	}

	float ConfigFile::GetFloat(const char* optname, float def) const
	{
		ConfigEntry ent = Get(optname);
		if (ent.IsValid())
		{
			return ent.GetValueFloat();
		}
		return def;
	}

	Vec4f ConfigFile::GetVec4f(const char* optname, const Vec4f& def) const
	{
		ConfigEntry ent = Get(optname);
		if (ent.IsValid())
		{
			return ent.GetValueVec4f();
		}
		return def;
	}

	void ConfigFile::SetNcf(NCF* n)
	{
		if (m_OwnNcf)
			delete m_Ncf;
		m_Ncf = n;
		m_Valid = true;
		m_OwnNcf = false;
	}


	NCF* ConfigFile::GetNcf()
	{
		return m_Ncf;
	}

	// --- ConfigEntry ---
	ConfigEntry::ConfigEntry()
	{
		m_Name = m_ValueString = nullptr;
	}

	ConfigEntry::ConfigEntry(const char* name, const char* val)
	{
		this->m_Name = name;
		m_ValueString = val;
	}

	bool ConfigEntry::IsValid() const
	{
		return m_ValueString != nullptr;
	}

	const char* ConfigEntry::GetName() const
	{
		return m_Name;
	}

	const char* ConfigEntry::GetValueString() const
	{
		return m_ValueString;
	}

	bool ConfigEntry::IsNumber() const
	{
		if (!m_ValueString)
		{
			return false;
		}

		char* endp;
		strtod(m_ValueString, &endp);

		return endp != m_ValueString;
	}

	int ConfigEntry::GetValueInt() const
	{
		return atoi(m_ValueString);
	}

	float ConfigEntry::GetValueFloat() const
	{
		return atof(m_ValueString);
	}

	Vec4f ConfigEntry::GetValueVec4f() const
	{
		float v[4] = { 0, 0, 0, 1 };
		sscanf(m_ValueString, "%f %f %f %f", v, v + 1, v + 2, v + 3);
		return Vec4f{ v[0], v[1], v[2], v[3] };
	}
}
