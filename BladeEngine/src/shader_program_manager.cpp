#include "shader_program_manager.h"
#include <iostream>
#include "d3d/D3D11_shader_program.h"

namespace Blade
{
	ShaderProgramMap ShaderProgramManager::m_ShaderProgramByName;

	ShaderProgramManager::~ShaderProgramManager()
	{
		for (auto it : m_ShaderProgramByName)
		{
			delete it.second;
		}

		m_ShaderProgramByName.clear();
	}

	bool ShaderProgramManager::Create(const std::string& prog_name,
	                                  unsigned input_layout_mask,
	                                  const std::wstring& vs,
	                                  const std::wstring& fs,
	                                  const std::wstring& hs,
	                                  const std::wstring& ds,
	                                  const std::wstring& gs) noexcept
	{
		ShaderProgram* sdr_prog{ m_ShaderProgramByName[prog_name] };

		if (sdr_prog)
		{
			std::cerr << "A shader program with the name provided already exists. Skipping creation." << std::endl;
			return false;
		}

#if defined(BLADE_BUILD_D3D)
		sdr_prog = new D3D11ShaderProgram;
#endif

		if (!sdr_prog->Create(input_layout_mask,
		                      vs,
		                      fs,
		                      hs,
		                      ds,
		                      gs))
		{
			return false;
		}

		m_ShaderProgramByName[prog_name] = sdr_prog;

		return true;
	}

	ShaderProgram* ShaderProgramManager::get(const std::string& prog_name) noexcept
	{
		return m_ShaderProgramByName[prog_name];
	}
}
