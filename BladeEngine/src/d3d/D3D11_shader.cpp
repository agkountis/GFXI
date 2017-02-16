#include "d3d/D3D11_shader.h"
#include <D3D/d3dx11async.h>
#include <fstream>
#include <map>
#include <iostream>

namespace Blade
{
	static std::map<std::wstring, std::string> shader_profiles{ // parasoft-suppress  PB-23 "It just a normal construction of a map using an initializer list"
		{ L"vs", "vs_5_0" },
		{ L"hs", "hs_5_0" },
		{ L"ds", "ds_5_0" },
		{ L"ps", "ps_5_0" }
	};

	bool D3D11Shader::Load(const std::wstring& file_name) noexcept
	{
		unsigned int first_dot{ file_name.find_first_of('.') };
		unsigned int last_dot{ file_name.find_last_of('.') };

		const std::wstring shader_type = file_name.substr(first_dot + 1, last_dot - (first_dot + 1));

		const std::string shader_profile{ shader_profiles[shader_type] };

		if (shader_profile.empty())
		{
			std::cerr << "Shader compilation failed!" << std::endl;
			std::cerr <<
					"Please provide a valid shader type in the file name. Shader filename format <name>.<type>.hlsl. eg: myshader.vs.hlsl"
					<< std::endl;

			return false;
		}

		ComPtr<ID3DBlob> compiler_errors;
		D3DX11CompileFromFile(file_name.c_str(),
		                      nullptr,
		                      nullptr,
		                      "main",
		                      shader_profile.c_str(),
		                      0,
		                      0,
		                      nullptr,
		                      m_ShaderBlob.ReleaseAndGetAddressOf(),
		                      compiler_errors.GetAddressOf(),
		                      nullptr);

		if (compiler_errors)
		{
			const char* compileErrors;
			unsigned long bufferSize, i;
			std::ofstream fout;
			// Get a pointer to the error message text buffer.
			compileErrors = static_cast<const char*>(compiler_errors->GetBufferPointer());

			// Get the length of the message.
			bufferSize = compiler_errors->GetBufferSize();

			// Open a file to write the error message to.
			fout.open(file_name + L".compilation_errors.txt");

			// Write out the error message.
			for (i = 0; i < bufferSize; i++)
			{
				fout << compileErrors[i];
			}

			// Close the file.
			fout.close();

			std::cerr << "Shader compilation failed!" << std::endl;
			std::cerr << "There were compilation errors. Please check the corresponding error file." << std::endl;

			return false;
		}

		return true;
	}
}
