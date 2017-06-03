#ifndef BLADE_SHADER_PROGRAM_MANAGER_H_
#define BLADE_SHADER_PROGRAM_MANAGER_H_
#include <map>
#include "shader_program.h"
#include "singleton.h"

namespace Blade
{
	class ShaderProgramManager : public Singleton<ShaderProgramManager>
	{
	private:
		std::map<std::string, ShaderProgram*> m_ShaderProgramByName;

	public:
		~ShaderProgramManager();

		bool Create(const ShaderProgramDesc& shaderProgramDesc) noexcept;

		ShaderProgram* Get(const std::string& progName) noexcept;
	};

#define STN_ShaderProgramManager ShaderProgramManager::GetInstance()
}

#endif //BLADE_SHADER_PROGRAM_MANAGER_H_
