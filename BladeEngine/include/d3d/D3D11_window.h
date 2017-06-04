#ifndef BLADE_D3D11WINDOW_H_
#define BLADE_D3D11WINDOW_H_
#include <D3D/d3d11.h>
#include "D3D11_render_target.h"
#include "win32_window.h"

namespace Blade
{
	class D3D11Context;

	class D3D11Window : public Win32Window {
	private:
		ComPtr<IDXGISwapChain> m_SwapChain;

		bool m_EnableMSAA{ false };
		int m_SampleCount{ 4 };
		unsigned int m_MSAAQuality;

		bool CreateSwapChain(D3D11Context& ctx);

		bool CreateRenderTargetView(D3D11Context& ctx) const noexcept;

		bool CreateDepthStencilView(D3D11Context& ctx) const noexcept;

		bool Initialize();

	public:
		D3D11Window(const std::wstring& title,
		            const Vec2i& size,
		            const Vec2i& position,
		            const unsigned int windowId,
		            const bool focused,
		            const bool minimized,
		            const bool resizeable,
		            const bool showCursor,
		            const bool enableMSAA,
		            const int msaaSampleCount,
		            const WindowFunctionCallbacks& callbacks) : Win32Window{ title,
			                                                        size,
			                                                        position,
			                                                        windowId,
			                                                        focused,
			                                                        minimized,
			                                                        resizeable,
			                                                        showCursor,
			                                                        callbacks },
		                                                        m_EnableMSAA{ enableMSAA },
		                                                        m_SampleCount{ msaaSampleCount },
																m_MSAAQuality{ 0 }
		{
			Initialize();
		}

		void EnableMSAA(bool state) noexcept
		{
			m_EnableMSAA = state;
		}

		bool MSAAEnabled() const noexcept
		{
			return m_EnableMSAA;
		}

		int GetSampleCount() const noexcept
		{
			return m_SampleCount;
		}

		unsigned int GetMSAAQuality() const noexcept
		{
			return m_MSAAQuality;
		}

		void SwapBuffers(unsigned syncInterval) const noexcept override;
	};
}

#endif //BLADE_D3D11WINDOW_H_
