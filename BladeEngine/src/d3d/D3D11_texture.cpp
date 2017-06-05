#include "d3d/D3D11_texture.h"
#include <D3D/D3DX11tex.h>
#include <iostream>
#include "d3d/D3D11_context.h"
#include "engine_context.h"

namespace Blade
{
	bool D3D11Texture::Load(const std::wstring& file_name) noexcept
	{
		ID3D11Device* device{ G_GAPIContext.GetDevice() };

		HRESULT res{ D3DX11CreateShaderResourceViewFromFile(device,
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
		ID3D11DeviceContext* device_context{ G_GAPIContext.GetDeviceContext() };

		device_context->PSSetShaderResources(GetTextureType(), 1, m_ShaderResourceView.GetAddressOf());
	}
}
