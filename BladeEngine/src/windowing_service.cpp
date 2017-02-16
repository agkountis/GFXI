#include "windowing_service.h"
#include "d3d/D3D11_window.h"
#include <algorithm>

namespace Blade
{
	std::vector<Window*> WindowingService::m_Windows;

	void WindowingService::AddWindow(class Window* window)
	{
		m_Windows.push_back(window);
	}

	void WindowingService::Create(const std::wstring& title,
	                              const Vec2i& size,
	                              const Vec2i& position,
	                              const bool focused,
	                              const bool minimized,
	                              const bool resizeable,
	                              const bool show_cursor,
	                              const bool enable_MSAA,
	                              const int MSAA_sample_count,
	                              const WindowFunctionCallbacks& callbacks)
	{
		Window* window;
#if defined(WIN32)
#if defined(BLADE_BUILD_D3D)
		window = new D3D11Window(title,
		                         size,
		                         position,
		                         m_Windows.size(),
		                         focused,
		                         minimized,
		                         resizeable,
		                         show_cursor,
		                         enable_MSAA,
		                         MSAA_sample_count,
		                         callbacks);
#elif defined(GLACIERENGINE_BUILD_OPENGL)
		//Create win32 GL window.
#endif
#elif defined(__APPLE__)
		//create Apple GL window.
#else
		//create Linux GL window.
#endif

		AddWindow(window);
	}


	void WindowingService::DestroyWindow(unsigned int win_id)
	{
		unsigned int id = win_id;
		auto it{ std::find_if(m_Windows.begin(), m_Windows.end(),
		                      [id](Window* win) -> bool
		                      {
			                      return id == win->GetId();
		                      }) };
		delete *it;
		m_Windows.erase(it);
	}

	Window* WindowingService::GetWindow(unsigned int win_id) noexcept
	{
		for (Window* win : m_Windows)
		{
			if (win->GetId() == win_id)
			{
				return win;
			}
		}

		return nullptr;
	}

	Window* WindowingService::GetWindow(const std::wstring& title) noexcept
	{
		for (Window* win : m_Windows)
		{
			if (win->GetTitle() == title)
			{
				return win;
			}
		}

		return nullptr;
	}

	size_t WindowingService::GetWindowCount() noexcept
	{
		return m_Windows.size();
	}


	void WindowingService::SwapBuffers() noexcept
	{
		for (const auto window : m_Windows)
		{
			window->SwapBuffers();
		}
	}
}
