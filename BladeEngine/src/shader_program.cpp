#include "shader_program.h"

namespace Blade
{
	ShaderProgram::ShaderProgram()
	{
		for (int i = 0; i < SHADER_COUNT; ++i)
		{
			m_Shaders[i] = nullptr;
		}
	}

	ShaderProgram::~ShaderProgram()
	{
	}
}
