#include "d3d/D3D11_depth_stencil_state.h"
#include <minwinbase.h>
#include "engine_context.h"

namespace Blade
{
	D3D11DepthStencilState::D3D11DepthStencilState(RenderStateType render_state_type)
	{
		switch (render_state_type)
		{
		case RenderStateType::DSS_DEPTH_TEST_DISABLE:
		{
			D3D11_DEPTH_STENCIL_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.DepthEnable = false;
			desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			desc.DepthFunc = D3D11_COMPARISON_LESS;
			desc.StencilEnable = false;
			desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
			desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
			desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;

			ID3D11Device* device{ G_GAPIContext.GetDevice() };

			HRESULT res{ device->CreateDepthStencilState(&desc, m_DepthStencilState.ReleaseAndGetAddressOf()) };
		}
			break;
		case RenderStateType::DSS_DEPTH_TEST_ENABLE:
		{
			D3D11_DEPTH_STENCIL_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.DepthEnable = true;
			desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			desc.DepthFunc = D3D11_COMPARISON_LESS;
			desc.StencilEnable = false;
			desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
			desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
			desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;

			ID3D11Device* device{ G_GAPIContext.GetDevice() };

			HRESULT res{ device->CreateDepthStencilState(&desc, m_DepthStencilState.ReleaseAndGetAddressOf()) };
		}
			break;
		case RenderStateType::DSS_DEPTH_MASK_0:
		{
			D3D11_DEPTH_STENCIL_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.DepthEnable = true;
			desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
			desc.DepthFunc = D3D11_COMPARISON_LESS;
			desc.StencilEnable = false;
			desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
			desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
			desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;

			ID3D11Device* device{ G_GAPIContext.GetDevice() };

			HRESULT res{ device->CreateDepthStencilState(&desc, m_DepthStencilState.ReleaseAndGetAddressOf()) };
		}
			break;
		case RenderStateType::DSS_DEPTH_MASK_1:
		{
			D3D11_DEPTH_STENCIL_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.DepthEnable = true;
			desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			desc.DepthFunc = D3D11_COMPARISON_LESS;
			desc.StencilEnable = false;
			desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
			desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
			desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;

			ID3D11Device* device{ G_GAPIContext.GetDevice() };

			HRESULT res{ device->CreateDepthStencilState(&desc, m_DepthStencilState.ReleaseAndGetAddressOf()) };
		}
			break;
		default:
			break;
		}
	}

	void D3D11DepthStencilState::Set() const noexcept
	{
		ID3D11DeviceContext* device_context{ G_GAPIContext.GetDeviceContext() };

		device_context->OMSetDepthStencilState(m_DepthStencilState.Get(), 0);
	}
}
