#ifndef BLADE_SHADER_PROGRAM_MANAGER_H_
#define BLADE_SHADER_PROGRAM_MANAGER_H_
#include <map>
#include "shader_program.h"

namespace Blade
{
	/*
	\brief Shader program manager of the engine.
	*/
	class ShaderProgramManager
	{
	private:
		/*
		\brief Associate shader program by name.
		*/
		std::map<std::string, ShaderProgram*> m_ShaderProgramByName;

	public:
		~ShaderProgramManager();

		/*
		\brief Create a new shader program
		\details If the shader program is already created do not re-create it.
		*/
		bool Create(const ShaderProgramDesc& shaderProgramDesc) noexcept;

		/*
		\brief Get the shader program by name
		\param progName the shader program name
		\return The shader program 
		*/
		ShaderProgram* Get(const std::string& progName) noexcept;
	};
}

#endif //BLADE_SHADER_PROGRAM_MANAGER_H_
