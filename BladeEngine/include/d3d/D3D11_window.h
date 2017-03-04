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
		ComPtr<IDXGISwapChain> m_swap_chain;

		bool m_enable_MSAA{ false };
		int m_sample_count{ 4 };
		unsigned int m_MSAA_quality;

		bool create_swap_chain(const D3D11Context* ctx);

		bool create_render_target_view(D3D11Context* ctx) const noexcept;

		bool create_depth_stencil_view(D3D11Context* ctx) const noexcept;

		bool initialize();

	public:
		D3D11Window(const std::wstring& title,
		            const Vec2i& size,
		            const Vec2i& position,
		            const unsigned int window_id,
		            const bool focused,
		            const bool minimized,
		            const bool resizeable,
		            const bool show_cursor,
		            const bool enable_MSAA,
		            const int MSAA_sample_count,
		            const WindowFunctionCallbacks& callbacks) : Win32Window{ title,
			                                                        size,
			                                                        position,
			                                                        window_id,
			                                                        focused,
			                                                        minimized,
			                                                        resizeable,
			                                                        show_cursor,
			                                                        callbacks },
		                                                        m_enable_MSAA{ enable_MSAA },
		                                                        m_sample_count{ MSAA_sample_count },
																m_MSAA_quality{ 0 }
		{
			initialize();
		}

		void enable_MSAA(bool state) noexcept
		{
			m_enable_MSAA = state;
		}

		bool MSAA_enabled() const noexcept
		{
			return m_enable_MSAA;
		}

		int get_sample_count() const noexcept
		{
			return m_sample_count;
		}

		unsigned int get_MSAA_quality() const noexcept
		{
			return m_MSAA_quality;
		}

		void SwapBuffers() const noexcept override;
	};
}

#endif //BLADE_D3D11WINDOW_H_
