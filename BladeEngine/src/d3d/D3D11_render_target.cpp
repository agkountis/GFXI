#include "d3d/D3D11_render_target.h"
#include "d3d/D3D11_context.h"
#include <iostream>
#include "engine_context.h"

namespace Blade
{
	bool D3D11RenderTarget::Create(const Vec2i& size)
	{
		SetSize(size);

		D3D11Context* ctx{ EngineContext::GetGAPIContext() };

		ID3D11Device* device{ ctx->GetDevice() };

		HRESULT res{ 0 };

		D3D11_TEXTURE2D_DESC color_attachment_desc;
		color_attachment_desc.Width = GetSize().x;
		color_attachment_desc.Height = GetSize().y;
		color_attachment_desc.MipLevels = 1;
		color_attachment_desc.ArraySize = 1;
		color_attachment_desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

		if (m_MSAA)
		{
			color_attachment_desc.SampleDesc.Count = m_SampleCount;
			color_attachment_desc.SampleDesc.Quality = ctx->GetMSAAQuality(m_SampleCount) - 1;
		}
		else
		{
			color_attachment_desc.SampleDesc.Count = 1;
			color_attachment_desc.SampleDesc.Quality = 0;
		}

		color_attachment_desc.Usage = D3D11_USAGE_DEFAULT;
		color_attachment_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		color_attachment_desc.CPUAccessFlags = 0;
		color_attachment_desc.MiscFlags = 0;

		res = device->CreateTexture2D(&color_attachment_desc, nullptr, m_ColorAttachment.ReleaseAndGetAddressOf());

		if (FAILED(res))
		{
			std::cerr << "Failed to Create the D3D11RenderTarget color attachment!" << std::endl;
			return false;
		}

		D3D11_RENDER_TARGET_VIEW_DESC rtv_desc;
		rtv_desc.Format = color_attachment_desc.Format;
		rtv_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtv_desc.Texture2D.MipSlice = 0;

		res = device->CreateRenderTargetView(m_ColorAttachment.Get(), &rtv_desc, m_RenderTargetView.ReleaseAndGetAddressOf());
		if (FAILED(res))
		{
			std::cerr << "Failed to create the D3D11RenderTarget render target view!" << std::endl;
			return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC color_srv_desc;
		color_srv_desc.Format = color_attachment_desc.Format;
		color_srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		color_srv_desc.Texture2D.MostDetailedMip = 0;
		color_srv_desc.Texture2D.MipLevels = 1;

		// Create the shader resource view.
		res = device->CreateShaderResourceView(m_ColorAttachment.Get(), &color_srv_desc, m_ColorAttachmentSrv.ReleaseAndGetAddressOf());
		if (FAILED(res))
		{
			std::cerr << "Failed to create the color attachment shader resource view!" << std::endl;
			return false;
		}

		D3D11_TEXTURE2D_DESC depth_attachment_desc;
		depth_attachment_desc.Width = GetSize().x;
		depth_attachment_desc.Height = GetSize().y;
		depth_attachment_desc.MipLevels = 1;
		depth_attachment_desc.ArraySize = 1;
		depth_attachment_desc.Format = DXGI_FORMAT_R24G8_TYPELESS;

		if (m_MSAA)
		{
			depth_attachment_desc.SampleDesc.Count = m_SampleCount;
			depth_attachment_desc.SampleDesc.Quality = ctx->GetMSAAQuality(m_SampleCount) - 1;
		}
		else
		{
			depth_attachment_desc.SampleDesc.Count = 1;
			depth_attachment_desc.SampleDesc.Quality = 0;
		}

		depth_attachment_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_attachment_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		depth_attachment_desc.CPUAccessFlags = 0;
		depth_attachment_desc.MiscFlags = 0;

		res = device->CreateTexture2D(&depth_attachment_desc, nullptr, m_DepthAttachment.ReleaseAndGetAddressOf());

		if (FAILED(res))
		{
			std::cerr << "Failed to create D3D11RenderTarget depth attachment!" << std::endl;
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC desc_dsv;
		desc_dsv.Flags = 0;
		desc_dsv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc_dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc_dsv.Texture2D.MipSlice = 0;

		res = device->CreateDepthStencilView(m_DepthAttachment.Get(), &desc_dsv, m_DepthStencilView.ReleaseAndGetAddressOf());

		if (FAILED(res))
		{
			std::cerr << "Failed to create D3D11RenderTarget depth stencil view!" << std::endl;
			return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC depth_srv_desc;
		depth_srv_desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		depth_srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		depth_srv_desc.Texture2D.MipLevels = depth_attachment_desc.MipLevels;
		depth_srv_desc.Texture2D.MostDetailedMip = 0;

		res = device->CreateShaderResourceView(m_DepthAttachment.Get(), &depth_srv_desc, m_DepthAttachmentSrv.ReleaseAndGetAddressOf());

		if (FAILED(res))
		{
			std::cerr << "Failed to create the depth attachment shader resource view!" << std::endl;
			return false;
		}

		return true;
	}

	bool D3D11RenderTarget::Bind(RenderTargetBindType bind_type) const
	{
		D3D11Context* ctx{ EngineContext::GetGAPIContext() };

		ID3D11DeviceContext* context{ ctx->GetDeviceContext() };

		switch (bind_type)
		{
		case RenderTargetBindType::COLOR_AND_DEPTH:
			context->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
			break;
		case RenderTargetBindType::DEPTH:
			context->OMSetRenderTargets(0, nullptr, m_DepthStencilView.Get());
			break;
		default:
			break;
		}


		return true;
	}

	bool D3D11RenderTarget::Unbind() const
	{
		D3D11Context* ctx{ EngineContext::GetGAPIContext() };

		ID3D11DeviceContext* context{ ctx->GetDeviceContext() };
		ID3D11DepthStencilView* null_dsv{ nullptr };
		ID3D11RenderTargetView* null_rtvs{ nullptr };
		context->OMSetRenderTargets(1, &null_rtvs, null_dsv);

		return true;
	}

	void D3D11RenderTarget::Clear(float* color) const noexcept
	{
		D3D11Context* GAPI_context{ EngineContext::GetGAPIContext() };

		ID3D11DeviceContext* device_context{ GAPI_context->GetDeviceContext() };

		device_context->ClearRenderTargetView(m_RenderTargetView.Get(), color);
		device_context->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}
