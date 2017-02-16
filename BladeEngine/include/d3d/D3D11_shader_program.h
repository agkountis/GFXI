#ifndef GLACIER_D3D11_SHADER_PROGRAM_H_
#define GLACIER_D3D11_SHADER_PROGRAM_H_
#include "../shader_program.h"
#include "../types.h"
#include "D3D11_IBO.h"

namespace Blade
{
	class D3D11ShaderProgram : public ShaderProgram
	{
	private:
		ComPtr<ID3D11InputLayout> m_InputLayout;
		ComPtr<ID3D11VertexShader> m_VertexShader;
		ComPtr<ID3D11HullShader> m_HullShader;
		ComPtr<ID3D11DomainShader> m_DomainShader;
		ComPtr<ID3D11GeometryShader> m_GeometryShader;
		ComPtr<ID3D11PixelShader> m_PixelShader;

	public:
		D3D11ShaderProgram() = default;

		bool Create(unsigned int inputLayoutMask,
		            const std::wstring& vs,
		            const std::wstring& fs,
		            const std::wstring& hs,
		            const std::wstring& ds,
		            const std::wstring& gs) noexcept override;

		void Bind() const noexcept override;
	};
}

#endif //GLACIER_D3D11_SHADER_PROGRAM_H_
