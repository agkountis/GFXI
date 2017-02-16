#ifndef BLADE_SHADER_PROGRAM_MANAGER_H_
#define BLADE_SHADER_PROGRAM_MANAGER_H_
#include <map>
#include "shader_program.h"

namespace Blade
{
	using ShaderProgramMap = std::map<std::string, ShaderProgram*>;

	class ShaderProgramManager
	{
	private:
		static ShaderProgramMap m_ShaderProgramByName;

	public:
		ShaderProgramManager() = default;

		~ShaderProgramManager();

		ShaderProgramManager(const ShaderProgramManager&) = delete;

		ShaderProgramManager& operator=(const ShaderProgramManager&) = delete;

		static bool Create(const std::string& progName,
		                   unsigned int inputLayoutMask,
		                   const std::wstring& vs,
		                   const std::wstring& fs = L"",
		                   const std::wstring& hs = L"",
		                   const std::wstring& ds = L"",
		                   const std::wstring& gs = L"") noexcept;

		static ShaderProgram* get(const std::string& progName) noexcept;
	};
}

#endif //BLADE_SHADER_PROGRAM_MANAGER_H_
