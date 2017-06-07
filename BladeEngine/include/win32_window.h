#ifndef BLADE_WIN32_WINDOW_H_
#define BLADE_WIN32_WINDOW_H_

#include "window.h"
#include "trace.h"

#include <hidusage.h>
#include <map>

namespace Blade
{
	class Win32Window : public Window
	{
	private:
		class WindowClass
		{
		private:
			static const std::wstring m_WinClassName;
			static int m_Count;

		public:
			WindowClass();
			~WindowClass();

			WindowClass(const WindowClass&) = delete;

			WindowClass& operator=(const WindowClass&) = delete;

			static const std::wstring& GetWinClassName()
			{
				return m_WinClassName;
			}
		};

		const WindowClass m_WindowClass;

		static LRESULT CALLBACK _WinProcDef(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam);

		HWND m_Handle;
		HWND m_Parent;
		HMENU m_Menu;

		unsigned int m_Flags{ 0 };
		unsigned int m_FlagsEx{ 0 };

	public:
		Win32Window(const std::wstring& title,
		            const Vec2i& size,
		            const Vec2i& position,
		            const unsigned int windowId,
		            const bool focused,
		            const bool minimized,
		            const bool resizeable,
		            const bool show_cursor,
		            const WindowFunctionCallbacks& callbacks);

		virtual LRESULT CALLBACK WinProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam);

		Win32Window(const Win32Window&) = delete;

		Win32Window& operator=(const Win32Window&) = delete;

		HWND GetHandle() const
		{
			return m_Handle;
		}

		void SetHandle(HWND hwnd)
		{
			m_Handle = hwnd;
		}

		HWND GetParent() const
		{
			return m_Parent;
		}

		void SetParent(HWND hwnd)
		{
			m_Parent = hwnd;
		}

		HMENU GetMenu() const
		{
			return m_Menu;
		}

		void SetMenu(HMENU hmenu)
		{
			m_Menu = hmenu;
		}

		unsigned int GetFlags() const
		{
			return m_Flags;
		}

		void SetFlags(unsigned int flags)
		{
			m_Flags = flags;
		}

		unsigned int GetFlagsEx() const
		{
			return m_FlagsEx;
		}

		void SetFlagsEx(unsigned int flags_ex)
		{
			m_FlagsEx = flags_ex;
		}
	};
}
#endif //BLADE_WIN32_WINDOW_H_
