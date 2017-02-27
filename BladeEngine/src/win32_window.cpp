#include "win32_window.h"
#include <sstream>
#include <iostream>
#include "win32_utils.h"

namespace Blade
{
	const std::wstring Win32Window::WindowClass::m_WinClassName{ L"BladeWindowClass" };
	int Win32Window::WindowClass::m_Count{ 0 };

	// Private Class implementation ----------------------------------------------------------------
	Win32Window::WindowClass::WindowClass()
	{
		if (m_Count <= 0)
		{
			WNDCLASSEX wc = { 0 };
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = GetModuleHandle(nullptr);
			wc.style = (CS_HREDRAW | CS_VREDRAW);
			wc.lpfnWndProc = _WinProcDef;
			wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
			wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
			wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
			wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
			wc.lpszMenuName = nullptr;
			wc.lpszClassName = m_WinClassName.c_str();

			if (!::RegisterClassEx(&wc))
			{
				std::ostringstream ostr;

				ostr << "Unable to register window class '" << m_WinClassName.c_str() << "'";

				throw std::runtime_error(ostr.str().c_str());
			}
		}

		++m_Count;
	}

	Win32Window::WindowClass::~WindowClass()
	{
		--m_Count;

		if (m_Count >= 0)
		{
			UnregisterClass(m_WinClassName.c_str(), ::GetModuleHandle(nullptr));
		}
	}

	// ---------------------------------------------------------------------------------------------


	Win32Window::Win32Window(const std::wstring& title,
	                         const Vec2i& size,
	                         const Vec2i& position,
	                         const unsigned int window_id,
	                         const bool focused,
	                         const bool minimized,
	                         const bool resizeable,
	                         const bool show_cursor,
	                         const WindowFunctionCallbacks& callbacks) : Window(title,
	                                                                            size,
	                                                                            position,
	                                                                            window_id,
	                                                                            focused,
	                                                                            minimized,
	                                                                            resizeable,
	                                                                            show_cursor,
	                                                                            callbacks),
	                                                                     m_Handle{ nullptr },
	                                                                     m_Parent{ nullptr },
	                                                                     m_Menu{ nullptr }

	{
		RECT wr = { 0, 0, size.x, size.y };

		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);

		const unsigned int window_flags_enable{
			WS_CLIPCHILDREN |
			WS_CLIPSIBLINGS |
			WS_OVERLAPPEDWINDOW |
			WS_VISIBLE
		};

		const unsigned int window_flags_disable{ WS_DLGFRAME };
		const unsigned int window_flags_ex_enable{ WS_EX_CLIENTEDGE };
		const unsigned int window_flags_ex_disable{ 0 };

		m_Flags = window_flags_enable & ~window_flags_disable;
		m_FlagsEx = window_flags_ex_enable & ~window_flags_ex_disable;

		m_Handle = ::CreateWindowEx(m_FlagsEx,
		                            WindowClass::GetWinClassName().c_str(),
		                            title.c_str(),
		                            m_Flags,
		                            position.x,
		                            position.y,
		                            size.x,
		                            size.y,
		                            m_Parent,
		                            m_Menu,
		                            ::GetModuleHandle(nullptr),
		                            this); //Carry the window class pointer.

		//		if (!m_handle) {
		//			char buff[256];
		//			snprintf(buff, 256, "Error creating window with name: '%s'", title);
		//
		//			throw std::runtime_error(buff);
		//		}

		ShowWindow(m_Handle, SW_SHOWDEFAULT);
		UpdateWindow(m_Handle);
		SetShowCursor(Window::ShowCursor());
	}

	LRESULT CALLBACK Win32Window::WinProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		auto callbacks{ GetCallbacks() };

		switch (msg)
		{
		case WM_PAINT:
			ValidateRect(handle, nullptr);
			break;
		case WM_CLOSE:
			break;
		case WM_SIZE:
			SetSize(Vec2i{ LOWORD(lparam), HIWORD(lparam) });
			if (callbacks.reshape_func)
			{
				callbacks.reshape_func(GetSize().x, GetSize().y);
			}
			break;
		case WM_KEYDOWN:
			if (wparam < 256)
			{
				if (callbacks.keyboard_func)
				{
					callbacks.keyboard_func(wparam, GetMousePosition().x, GetMousePosition().y);
				}
			}
			else
			{
				if (callbacks.special_func)
				{
					callbacks.special_func(wparam, GetMousePosition().x, GetMousePosition().y);
				}
			}
			break;
		case WM_KEYUP:
			if (wparam < 256)
			{
				if (callbacks.keyboard_up_func)
				{
					callbacks.keyboard_up_func(wparam, GetMousePosition().x, GetMousePosition().y);
				}
			}
			else
			{
				if (callbacks.special_up_func)
				{
					callbacks.special_up_func(wparam, GetMousePosition().x, GetMousePosition().y);
				}
			}
			break;
		case WM_MOUSEMOVE:
			SetMousePosition(Vec2i{ LOWORD(lparam), HIWORD(lparam) });
			if (wparam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON))
			{
				if (callbacks.motion_func)
				{
					callbacks.motion_func(GetMousePosition().x, GetMousePosition().y);
				}
			}
			else
			{
				if (callbacks.passive_motion_func)
				{
					callbacks.passive_motion_func(GetMousePosition().x, GetMousePosition().y);
				}
			}
			break;
		case WM_LBUTTONDOWN:
			if (callbacks.mouse_func)
			{
				callbacks.mouse_func(0, true, LOWORD(lparam), HIWORD(lparam));
			}
			break;
		case WM_RBUTTONDOWN:
			if (callbacks.mouse_func)
			{
				callbacks.mouse_func(2, true, LOWORD(lparam), HIWORD(lparam));
			}
			break;
		case WM_MBUTTONDOWN:
			if (callbacks.mouse_func)
			{
				callbacks.mouse_func(1, true, LOWORD(lparam), HIWORD(lparam));
			}
			break;
		case WM_LBUTTONUP:
			if (callbacks.mouse_func)
			{
				callbacks.mouse_func(0, false, LOWORD(lparam), HIWORD(lparam));
			}
			break;
		case WM_RBUTTONUP:
			if (callbacks.mouse_func)
			{
				callbacks.mouse_func(2, false, LOWORD(lparam), HIWORD(lparam));
			}
			break;
		case WM_MBUTTONUP:
			if (callbacks.mouse_func)
			{
				callbacks.mouse_func(1, false, LOWORD(lparam), HIWORD(lparam));
			}
			break;
		case WM_MOUSEWHEEL:
			//int delta = GET_WHEEL_DELTA_WPARAM(wparam);
			break;
		case WM_DESTROY:
			PostQuitMessage(WM_QUIT);
			break;
		default:
			break;
		}

		return DefWindowProc(handle, msg, wparam, lparam);
	}


	LRESULT CALLBACK Win32Window::_WinProcDef(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
		case WM_NCCREATE:
		case WM_NCDESTROY:
		{
			Win32Window* win{ nullptr };
			if (msg == WM_NCCREATE)
			{
				//extract the Win32Window we stored in the window creation from the lparam.
				win = static_cast<Win32Window*>(reinterpret_cast<CREATESTRUCT*>(lparam)->lpCreateParams);
			}

			//map the window with it's handle.
			SetWindowLongPointer(handle, GWL_USERDATA, win);

			return DefWindowProc(handle, msg, wparam, lparam);
		}
		default:
			break;
		}

		Win32Window* win{ nullptr };
		//get the window by it's handle
		win = GetWindowLongPointer<Win32Window>(handle, GWL_USERDATA);
		if (win)
		{
			//execute the window specific win_proc.
			return win->WinProc(handle, msg, wparam, lparam);
		}

		return DefWindowProc(handle, msg, wparam, lparam);
	}
}
