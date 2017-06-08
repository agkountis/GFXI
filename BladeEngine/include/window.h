#ifndef BLADE_WINDOW_H_
#define BLADE_WINDOW_H_
#include <string>
#include "types.h"
#include "windowing_types.h"

namespace Blade
{
	/*
	\brief Window class of the engine. It represents a platform independent window.
	*/
	class Window
	{
	private:
		/*
		\brief Window title
		*/
		std::wstring m_Title;

		/*
		\brief Window size
		*/
		Vec2i m_Size;

		/*
		\brief Window position
		*/
		Vec2i m_Position;

		/*
		\brief Window unique ID
		\details Multiple windows are fully supported.
		*/
		unsigned int m_WinId{ 0 };

		Vec2i m_MousePos;

		bool m_Focused{ true };
		bool m_Minimized{ false };
		bool m_Resizeable{ true };
		bool m_ShowCursor{ true };

		bool m_ChangedSize{ false };
		bool m_Redisplay{ true };

		WindowFunctionCallbacks m_Callbacks;

	public:
		explicit Window(const std::wstring& title,
		                const Vec2i& size,
		                const Vec2i& position,
		                const unsigned int windowId,
		                const bool focused,
		                const bool minimized,
		                const bool resizeable,
		                const bool showCursor,
		                const WindowFunctionCallbacks& callbacks) : m_Title{ title },
		                                                            m_Size{ size },
		                                                            m_Position{ position },
		                                                            m_WinId{ windowId },
		                                                            m_Focused{ focused },
		                                                            m_Minimized{ minimized },
		                                                            m_Resizeable{ resizeable },
		                                                            m_ShowCursor{ showCursor },
		                                                            m_ChangedSize{ false },
		                                                            m_Redisplay{ true },
		                                                            m_Callbacks{ callbacks }
		{
		}

		Window(const Window& win) = delete;

		Window& operator=(const Window& win) = delete;

		virtual ~Window();

		const std::wstring& GetTitle() const noexcept
		{
			return m_Title;
		}

		void SetSize(const Vec2i& size) noexcept
		{
			m_Size = size;
		}

		const Vec2i& GetSize() const noexcept
		{
			return m_Size;
		}

		unsigned int GetId() const noexcept
		{
			return m_WinId;
		}

		const Vec2i& GetMousePosition() const noexcept
		{
			return m_MousePos;
		}

		void SetMousePosition(const Vec2i& mousePos) noexcept
		{
			m_MousePos = mousePos;
		}

		void SetFocus(const bool focus) noexcept
		{
			m_Focused = focus;
		}

		bool IsFocused() const noexcept
		{
			return m_Focused;
		}

		void SetMinimized(const bool minimized) noexcept
		{
			m_Minimized = minimized;
		}

		bool IsMinimized() const noexcept
		{
			return m_Minimized;
		}

		void SetResizable(const bool resizeable) noexcept
		{
			m_Resizeable = resizeable;
		}

		bool IsResizeable() const noexcept
		{
			return m_Resizeable;
		}

		void SetChangedSize(const bool state) noexcept
		{
			m_ChangedSize = state;
		}

		bool ChangedSize() const noexcept
		{
			return m_ChangedSize;
		}

		void SetRedisplay(const bool redisplay) noexcept
		{
			m_Redisplay = redisplay;
		}

		void SetShowCursor(bool show) noexcept
		{
			m_ShowCursor = show;
		}

		bool ShowCursor() const noexcept
		{
			return m_ShowCursor;
		}

		void SetWindowCallbacks(const WindowFunctionCallbacks& callbacks) noexcept
		{
			m_Callbacks = callbacks;
		}

		const WindowFunctionCallbacks& GetCallbacks() const noexcept
		{
			return m_Callbacks;
		}

		virtual void SwapBuffers(unsigned syncInterval = 0) const noexcept = 0;
	};
}

#endif //BLADE_WINDOW_H_
