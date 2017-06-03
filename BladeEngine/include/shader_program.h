#ifndef BLADE_SHADER_PROGRAM_H_
#define BLADE_SHADER_PROGRAM_H_
#include "shader.h"
#include "d3d/D3D11_shader.h"
#include <array>

namespace Blade
{
	enum InputLayoutMask
	{
		IL_POSITION = 0x02,
		IL_NORMAL = 0x04,
		IL_TANGENT = 0x08,
		IL_TEXCOORD = 0x10,
		IL_COLOR = 0x20
	};

	static const std::wstring SHADER_PATH{ L"sdr\\" };

	struct ShaderProgramDesc
	{
		std::string name;
		unsigned int inputLayoutMask;
		std::wstring vertexShader;
		std::wstring fragmentShader;
		std::wstring hullShader;
		std::wstring domainShader;
		std::wstring geometryShader;
	};

	class ShaderProgram
	{
	private:
#if defined(BLADE_BUILD_D3D)
		std::array<D3D11Shader*, SHADER_COUNT> m_Shaders;
#else
#endif
	public:
		ShaderProgram();

		virtual ~ShaderProgram();

		ShaderProgram(const ShaderProgram&) = default;

		ShaderProgram& operator=(const ShaderProgram&) = default;

#if defined(BLADE_BUILD_D3D)
		D3D11Shader* GetShader(ShaderType shaderType)
		{
			return m_Shaders[shaderType];
		}

		void SetShader(D3D11Shader* shader, ShaderType shaderType) noexcept
		{
			m_Shaders[shaderType] = shader;
		}
#else
#endif

		virtual bool Create(const ShaderProgramDesc& shaderProgramDesc) noexcept = 0;

		virtual void Bind() const noexcept = 0;
	};
}

#endif //BLADE_SHADER_PROGRAM_H_
