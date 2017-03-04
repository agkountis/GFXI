#include "d3d/D3D11_rasterizer_state.h"
#include "d3d/D3D11_context.h"
#include "engine_context.h"
#include <minwinbase.h>

namespace Blade
{
	D3D11RasterizerState::D3D11RasterizerState(RenderStateType render_state_type)
	{
		switch (render_state_type)
		{
		case RenderStateType::RS_CULL_BACK:
		{
			D3D11_RASTERIZER_DESC rasterizer_desc;
			ZeroMemory(&rasterizer_desc, sizeof(rasterizer_desc));
			rasterizer_desc.FillMode = D3D11_FILL_SOLID;
			rasterizer_desc.CullMode = D3D11_CULL_BACK;
			rasterizer_desc.FrontCounterClockwise = false;
			rasterizer_desc.DepthBias = 0;
			rasterizer_desc.SlopeScaledDepthBias = 0;
			rasterizer_desc.DepthBiasClamp = 0.0f;
			rasterizer_desc.DepthClipEnable = true;
			rasterizer_desc.ScissorEnable = false;
			rasterizer_desc.MultisampleEnable = false;
			rasterizer_desc.AntialiasedLineEnable = false;

			D3D11Context* GAPI_context{ EngineContext::get_GAPI_context() };
			ComPtr<ID3D11Device> device{ GAPI_context->GetDevice() };

			HRESULT res = device->CreateRasterizerState(&rasterizer_desc, m_RasterizerState.ReleaseAndGetAddressOf());
		}
			break;
		case RenderStateType::RS_CULL_FRONT:
		{
			D3D11_RASTERIZER_DESC rasterizer_desc;
			ZeroMemory(&rasterizer_desc, sizeof(rasterizer_desc));
			rasterizer_desc.FillMode = D3D11_FILL_SOLID;
			rasterizer_desc.CullMode = D3D11_CULL_FRONT;
			rasterizer_desc.FrontCounterClockwise = false;
			rasterizer_desc.DepthBias = 0;
			rasterizer_desc.SlopeScaledDepthBias = 0;
			rasterizer_desc.DepthBiasClamp = 0.0f;
			rasterizer_desc.DepthClipEnable = true;
			rasterizer_desc.ScissorEnable = false;
			rasterizer_desc.MultisampleEnable = false;
			rasterizer_desc.AntialiasedLineEnable = false;

			D3D11Context* GAPI_context{ EngineContext::get_GAPI_context() };
			ComPtr<ID3D11Device> device{ GAPI_context->GetDevice() };

			HRESULT res = device->CreateRasterizerState(&rasterizer_desc, m_RasterizerState.ReleaseAndGetAddressOf());
		}
			break;
		case RenderStateType::RS_DRAW_SOLID:
		{
			D3D11_RASTERIZER_DESC rasterizer_desc;
			ZeroMemory(&rasterizer_desc, sizeof(rasterizer_desc));
			rasterizer_desc.FillMode = D3D11_FILL_SOLID;
			rasterizer_desc.CullMode = D3D11_CULL_BACK;
			rasterizer_desc.FrontCounterClockwise = false;
			rasterizer_desc.DepthBias = 0;
			rasterizer_desc.SlopeScaledDepthBias = 0;
			rasterizer_desc.DepthBiasClamp = 0.0f;
			rasterizer_desc.DepthClipEnable = true;
			rasterizer_desc.ScissorEnable = false;
			rasterizer_desc.MultisampleEnable = false;
			rasterizer_desc.AntialiasedLineEnable = false;

			D3D11Context* GAPI_context{ EngineContext::get_GAPI_context() };
			ComPtr<ID3D11Device> device{ GAPI_context->GetDevice() };

			HRESULT res = device->CreateRasterizerState(&rasterizer_desc, m_RasterizerState.ReleaseAndGetAddressOf());
		}
			break;
		case RenderStateType::RS_DRAW_WIRE:
		{
			D3D11_RASTERIZER_DESC rasterizer_desc;
			ZeroMemory(&rasterizer_desc, sizeof(rasterizer_desc));
			rasterizer_desc.FillMode = D3D11_FILL_WIREFRAME;
			rasterizer_desc.CullMode = D3D11_CULL_BACK;
			rasterizer_desc.FrontCounterClockwise = false;
			rasterizer_desc.DepthBias = 0;
			rasterizer_desc.SlopeScaledDepthBias = 0;
			rasterizer_desc.DepthBiasClamp = 0.0f;
			rasterizer_desc.DepthClipEnable = true;
			rasterizer_desc.ScissorEnable = false;
			rasterizer_desc.MultisampleEnable = false;
			rasterizer_desc.AntialiasedLineEnable = false;

			D3D11Context* GAPI_context{ EngineContext::get_GAPI_context() };
			ComPtr<ID3D11Device> device{ GAPI_context->GetDevice() };

			HRESULT res = device->CreateRasterizerState(&rasterizer_desc, m_RasterizerState.ReleaseAndGetAddressOf());
		}
			break;
		default:
			break;
		}
	}

	void D3D11RasterizerState::Set() const noexcept
	{
		D3D11Context* GAPI_context{ EngineContext::get_GAPI_context() };

		ComPtr<ID3D11DeviceContext> device_context{ GAPI_context->GetDeviceContext() };

		device_context->RSSetState(m_RasterizerState.Get());
	}
}
