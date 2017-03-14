#include "d3d/D3D11_IBO.h"
#include "d3d/D3D11_context.h"
#include <iostream>
#include "engine_context.h"
#include <minwinbase.h>

namespace Blade
{
	bool D3D11IBO::Create(const std::vector<unsigned int>& indices) noexcept
	{
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		buffer_desc.ByteWidth = sizeof(unsigned int) * indices.size();
		buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11Context* ctx{ EngineContext::get_GAPI_context() };

		ID3D11Device* device{ ctx->GetDevice() };

		HRESULT res = device->CreateBuffer(&buffer_desc, nullptr, m_IndexBuffer.ReleaseAndGetAddressOf());
		if (FAILED(res))
		{
			std::cerr << "Failed to create the D3D11IBO." << std::endl;
			return false;
		}

		D3D11_MAPPED_SUBRESOURCE index_data;
		ZeroMemory(&index_data, sizeof(index_data));

		ID3D11DeviceContext* device_context{ ctx->GetDeviceContext() };

		device_context->Map(m_IndexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &index_data);
		memcpy(index_data.pData, indices.data(), sizeof(unsigned int) * indices.size());
		device_context->Unmap(m_IndexBuffer.Get(), 0);

		SetIndexCount(indices.size());

		return true;
	}

	void D3D11IBO::Bind() const noexcept
	{
		D3D11Context* GAPI_context{ EngineContext::get_GAPI_context() };

		ID3D11DeviceContext* device_context{ GAPI_context->GetDeviceContext() };

		device_context->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	void D3D11IBO::Draw() const noexcept
	{
		D3D11Context* ctx{ EngineContext::get_GAPI_context() };

		ID3D11DeviceContext* device_context{ ctx->GetDeviceContext() };

		device_context->DrawIndexed(GetIndexCount(), 0, 0);
	}
}
