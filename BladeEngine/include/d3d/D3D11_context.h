#ifndef BLADE_D3D_CONTEXT_H_
#define BLADE_D3D_CONTEXT_H_
#include "../GAPI_context.h"
#include "D3D/d3d11.h"
#include "../types.h"

namespace Blade
{
	class D3D11Context : public GAPIContext
	{
	private:
		bool CreateD3D11DeviceAndContext(LUID* luid);

		ComPtr<ID3D11Device> m_Device;
		ComPtr<ID3D11DeviceContext> m_DeviceContext;
		ComPtr<ID3D11Debug> m_DebugInterface;

		ComPtr<ID3D11Texture2D> m_BackBuffer;
		ComPtr<ID3D11RenderTargetView> m_DefaultRtv;
		ComPtr<ID3D11DepthStencilView> m_DefaultDsv;

	public:
		D3D11Context() = default;

		bool Create(LUID* luid) override;

		ID3D11Device* GetDevice() const;
		ID3D11DeviceContext* GetDeviceContext() const;
		ID3D11Debug* GetDebugInterface() const noexcept { return m_DebugInterface.Get(); }

		ID3D11Texture2D* GetBackBuffer()const noexcept { return m_BackBuffer.Get(); }
		ID3D11Texture2D** GetAddressOfBackBuffer() noexcept { return m_BackBuffer.GetAddressOf(); }

		ID3D11RenderTargetView* GetDefaultRenderTargetView() const noexcept { return m_DefaultRtv.Get(); }
		ID3D11DepthStencilView* GetDefaultDepthStencilView() const noexcept { return m_DefaultDsv.Get(); }

		ID3D11RenderTargetView** GetGetAddressOfDefaultRenderTargetView() noexcept { return m_DefaultRtv.GetAddressOf(); }
		ID3D11DepthStencilView** GetAddressOfDefaultDepthStencilView() noexcept { return m_DefaultDsv.GetAddressOf(); }

		unsigned int GetMSAAQuality(int sample_count) const;
	};
}

#endif //BLADE_D3D_CONTEXT_H_
