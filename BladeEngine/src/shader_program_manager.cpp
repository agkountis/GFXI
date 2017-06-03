#include "shader_program_manager.h"
#include "d3d/D3D11_shader_program.h"
#include "trace.h"

namespace Blade
{
	ShaderProgramManager::~ShaderProgramManager()
	{
		for (auto it : m_ShaderProgramByName)
		{
			delete it.second;
		}

		m_ShaderProgramByName.clear();
	}

	bool ShaderProgramManager::Create(const ShaderProgramDesc& shaderProgramDesc) noexcept
	{
		ShaderProgram* sdr_prog{ m_ShaderProgramByName[shaderProgramDesc.name] };

		if (sdr_prog)
		{
			BLADE_ERROR("A shader program with the name provided already exists. Skipping creation.");
			return false;
		}

#if defined(BLADE_BUILD_D3D)
		sdr_prog = new D3D11ShaderProgram;
#endif

		if (!sdr_prog->Create(shaderProgramDesc))
		{
			return false;
		}

		m_ShaderProgramByName[shaderProgramDesc.name] = sdr_prog;

		return true;
	}

	ShaderProgram* ShaderProgramManager::Get(const std::string& prog_name) noexcept
	{
		return m_ShaderProgramByName[prog_name];
	}
}
