#include "d3d/D3D11_VBO.h"
#include "d3d/D3D11_context.h"
#include <iostream>
#include "engine_context.h"
#include <minwinbase.h>

namespace Blade
{
	bool D3D11VBO::Create(const std::vector<Vertex>& vertices, PrimitiveTopology primitive_topology) noexcept
	{
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		buffer_desc.ByteWidth = sizeof(Vertex) * vertices.size();
		buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


		D3D11Context* ctx{ EngineContext::get_GAPI_context() };

		ComPtr<ID3D11Device> device{ ctx->GetDevice() };
		HRESULT res = device->CreateBuffer(&buffer_desc, nullptr, m_VertexBuffer.ReleaseAndGetAddressOf());

		if (FAILED(res))
		{
			std::cerr << "Failed to create the D3D11VBO." << std::endl;
			return false;
		}

		ComPtr<ID3D11DeviceContext> device_context{ ctx->GetDeviceContext() };

		D3D11_MAPPED_SUBRESOURCE ms;
		device_context->Map(m_VertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
		memcpy(ms.pData, vertices.data(), sizeof(Vertex) * vertices.size());
		device_context->Unmap(m_VertexBuffer.Get(), 0);

		SetVertexCount(vertices.size());

		SetPrimitiveTopology(primitive_topology);

		return true;
	}


	void D3D11VBO::Bind() const noexcept
	{
		D3D11Context* GAPI_context{ EngineContext::get_GAPI_context() };

		ComPtr<ID3D11DeviceContext> device_context{ GAPI_context->GetDeviceContext() };

		UINT stride{ sizeof(Vertex) };
		UINT offset{ 0 };
		device_context->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

		switch (GetPrimitiveTopology())
		{
		case PrimitiveTopology::TRIANGLE_LIST:
			device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			break;
		case PrimitiveTopology::TRIANGLE_STRIP:
			device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			break;
		default:
			break;
		}
	}

	void D3D11VBO::Draw() const noexcept
	{
		D3D11Context* ctx{ EngineContext::get_GAPI_context() };

		ComPtr<ID3D11DeviceContext> device_context{ ctx->GetDeviceContext() };
		device_context->Draw(GetVertexCount(), 0);
	}
}
