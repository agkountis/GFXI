#ifndef CFG_H_
#define CFG_H_

#include <string>
#include <list>
#include "ncf.h"
#include "types.h"

namespace Blade
{
	class ConfigEntry;

	class ConfigFile {
	private:
		NCF *m_Ncf;
		bool m_OwnNcf;
		bool m_Valid;

	public:
		ConfigFile();
		ConfigFile(const char *fname);
		~ConfigFile();

		bool Open(const char *fname);

		bool IsOpen() const;

		ConfigEntry Get(const char *optname) const;
		std::list<ConfigEntry> GetAll(const char *groupname) const;

		// convenience functions
		const char *GetString(const char *optname, const char *def = nullptr) const;
		int GetInteger(const char *optname, int def = 0) const;
		float GetFloat(const char *optname, float def = 0.0f) const;
		Vec4f GetVec4f(const char *optname, const Vec4f& def = Vec4f{ 0.0f, 0.0f, 0.0f, 1.0f }) const;
		void SetNcf(NCF *n);
		NCF* GetNcf();
	};

	class ConfigEntry {
	private:
		const char* m_Name;
		const char* m_ValueString;

	public:
		ConfigEntry();
		ConfigEntry(const char *name, const char* value);

		bool IsValid() const;

		const char* GetName() const;
		const char* GetValueString() const;

		bool IsNumber() const;

		int GetValueInt() const;
		float GetValueFloat() const;
		Vec4f GetValueVec4f() const;
	};
}

#endif	// CFG_H_
