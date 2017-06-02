#ifndef BLADE_WINDOWING_SERVICE_H_
#define BLADE_WINDOWING_SERVICE_H_
#include "window.h"
#include <vector>

namespace Blade
{
	class WindowingService {
	private:
		static std::vector<Window*> m_Windows;

	public:
		WindowingService() = default;

		WindowingService(const WindowingService& service) = delete;

		WindowingService& operator=(const WindowingService& service) = delete;

		static void AddWindow(Window* window);

		static void Create(const std::wstring& title,
		            const Vec2i& size,
		            const Vec2i& position,
		            const bool focused,
		            const bool minimized,
		            const bool resizeable,
		            const bool showCursor,
		            const bool enableMSAA,
		            const int MSAASampleCount,
		            const WindowFunctionCallbacks& callbacks);

		//TODO: figure out a nice data structure for traversing and removing windows.
		static void DestroyWindow(unsigned int win_id);

		static Window* GetWindow(unsigned int win_id) noexcept;

		static Window* GetWindow(const std::wstring& title) noexcept;

		static size_t GetWindowCount() noexcept;

		static void SwapBuffers() noexcept;
	};
}

#endif //BLADE_WINDOWING_SERVICE_H_
