#include "d3d/D3D11_window.h"
#include <assert.h>
#include "d3d/D3D11_context.h"
#include <iostream>
#include "engine_context.h"


namespace Blade
{
	// Private Methods -----------------------------------------------------------------------------------------------------------------------------
	bool D3D11Window::CreateSwapChain(D3D11Context& ctx)
	{
		//Describe the swapchain
		DXGI_SWAP_CHAIN_DESC swap_chain_desc;
		swap_chain_desc.BufferDesc.Width = GetSize().x;
		swap_chain_desc.BufferDesc.Height = GetSize().y;
		swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
		swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		if (m_EnableMSAA) {
			swap_chain_desc.SampleDesc.Count = m_SampleCount;
			swap_chain_desc.SampleDesc.Quality = ctx.GetMSAAQuality(m_SampleCount) - 1;
		}
		else { //No MSAA
			swap_chain_desc.SampleDesc.Count = 0;
			swap_chain_desc.SampleDesc.Quality = 0;
		}

		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 1; //1 back buffer == Double buffering
		swap_chain_desc.OutputWindow = GetHandle();
		swap_chain_desc.Windowed = true;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_chain_desc.Flags = 0;

		HRESULT h_result{ 0 };

		ComPtr<ID3D11Device> device{ ctx.GetDevice() };

		ComPtr<IDXGIDevice> dxgi_device{ nullptr };
		h_result = device.As(&dxgi_device);

		ComPtr<IDXGIAdapter> dxgi_adapter{ nullptr };
		h_result = dxgi_device->GetAdapter(dxgi_adapter.GetAddressOf());

		//Now get the factory interface that was used to create the m_device.
		ComPtr<IDXGIFactory> dxgi_factory{ nullptr };
		h_result = dxgi_adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(dxgi_factory.GetAddressOf()));

		//At last create the swap chain.
		h_result = dxgi_factory->CreateSwapChain(device.Get(), &swap_chain_desc, m_SwapChain.ReleaseAndGetAddressOf());

		if (FAILED(h_result)) {
			MessageBox(GetHandle(), L"DXGISwapChain creation failed.", nullptr, 0);
			return false;
		}

		return true;
	}

	bool D3D11Window::CreateRenderTargetView(D3D11Context& ctx) const noexcept
	{
		// get the address of the back buffer
		HRESULT res = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(G_GAPIContext.GetAddressOfBackBuffer()));

		if (FAILED(res)) {
			std::cerr << "Failed to get the adress of the back buffer." << std::endl;
			return false;
		}
		
		// use the back buffer address to create the render target
		ID3D11Device* device{ ctx.GetDevice() };
		res = device->CreateRenderTargetView(G_GAPIContext.GetBackBuffer(), nullptr, ctx.GetGetAddressOfDefaultRenderTargetView());

		if (FAILED(res)) {
			std::cerr << "Window render target view creation failed." << std::endl;
			return false;
		}

		return true;
	}

	bool D3D11Window::CreateDepthStencilView(D3D11Context& ctx) const noexcept
	{
		D3D11_TEXTURE2D_DESC depth_attachment_desc;
		ZeroMemory(&depth_attachment_desc, sizeof(depth_attachment_desc));
		depth_attachment_desc.Width = GetSize().x;
		depth_attachment_desc.Height = GetSize().y;
		depth_attachment_desc.MipLevels = 1;
		depth_attachment_desc.ArraySize = 1;
		depth_attachment_desc.Format = DXGI_FORMAT_D32_FLOAT;
		depth_attachment_desc.SampleDesc.Count = m_SampleCount;
		depth_attachment_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		ComPtr<ID3D11Texture2D> depth;
		ID3D11Device* device{ ctx.GetDevice() };
		HRESULT res = device->CreateTexture2D(&depth_attachment_desc, nullptr, depth.GetAddressOf());

		if (FAILED(res)) {
			std::cerr << "Failed to create the depth stencil view texture." << std::endl;
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = DXGI_FORMAT_D32_FLOAT;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

		res = device->CreateDepthStencilView(depth.Get(), &dsvd, ctx.GetAddressOfDefaultDepthStencilView());

		if (FAILED(res)) {
			std::cerr << "Window depth stencil view creation failed." << std::endl;
			return false;
		}

		return true;
	}

	bool D3D11Window::Initialize()
	{
		D3D11Context& ctx{ G_GAPIContext };

		if (!CreateSwapChain(ctx)) {
			return false;
		}

		if (!CreateRenderTargetView(ctx)) {
			return false;
		}

		if (!CreateDepthStencilView(ctx)) {
			return false;
		}

		D3D11_VIEWPORT viewport;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(GetSize().x);
		viewport.Height = static_cast<float>(GetSize().y);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		ID3D11DeviceContext* context{ ctx.GetDeviceContext() };
		context->RSSetViewports(1, &viewport);

		return true;
	}

	void D3D11Window::SwapBuffers(unsigned syncInterval) const noexcept
	{
		m_SwapChain->Present(syncInterval, 0);
	}

	// --------------------------------------------------------------------------------------------------------------------------------------------
}
