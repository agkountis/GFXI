#ifndef GLACIER_ENGINE_D3D11_SHADER_H_
#define GLACIER_ENGINE_D3D11_SHADER_H_
#include "shader.h"
#include "../types.h"
#include <D3D/d3d11.h>

namespace Blade
{
	class D3D11Shader : public Shader
	{
	private:
		ComPtr<ID3DBlob> m_ShaderBlob;

	public:
		D3D11Shader() = default;

		ID3DBlob* GetBlob() const noexcept
		{
			return m_ShaderBlob.Get();
		}

		bool Load(const std::wstring& fileName) noexcept override;
	};
}

#endif //GLACIER_ENGINE_D3D11_SHADER_H_
