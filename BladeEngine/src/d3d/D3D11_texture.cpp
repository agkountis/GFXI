#include "d3d/D3D11_texture.h"
#include <D3D/D3DX11tex.h>
#include <iostream>
#include "d3d/D3D11_context.h"
#include "engine_context.h"

namespace Blade
{
	bool D3D11Texture::Load(const std::wstring& file_name) noexcept
	{
		D3D11Context* context{ EngineContext::get_GAPI_context() };

		ComPtr<ID3D11Device> device{ context->GetDevice() };

		HRESULT res{ D3DX11CreateShaderResourceViewFromFile(device.Get(),
		                                                    file_name.c_str(),
		                                                    nullptr,
		                                                    nullptr,
		                                                    m_ShaderResourceView.ReleaseAndGetAddressOf(),
		                                                    nullptr) };

		if (FAILED(res))
		{
			std::wcerr << L"Failed to create texture from file " + file_name + L"! Shader resource view creation failed." << std::endl;
			return false;
		}

		return true;
	}

	void D3D11Texture::Bind() const noexcept
	{
		D3D11Context* GAPI_context{ EngineContext::get_GAPI_context() };

		ComPtr<ID3D11DeviceContext> device_context{ GAPI_context->GetDeviceContext() };

		device_context->PSSetShaderResources(GetTextureType(), 1, m_ShaderResourceView.GetAddressOf());
	}
}
