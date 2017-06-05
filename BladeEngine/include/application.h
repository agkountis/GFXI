#ifndef BLADE_APPLICATION_H_
#define BLADE_APPLICATION_H_
#include "engine_context.h"
#include "timer.h"

namespace Blade
{
	class Application
	{
	private:
		bool m_Terminate{ false };

		bool m_Paused{ false };

		Timer m_Timer;

	public:
		Application() = default;
		
		Application(const Application& application) = delete;
		
		Application& operator=(const Application& application) = delete;

		virtual ~Application() = default;

		void SetTermination(bool state) noexcept;

		bool ShouldTerminate() const noexcept;
		
		double GetDelta() const noexcept;

		long GetMsec() const noexcept;

		double GetSec() const noexcept;

		void Pause() noexcept;

		void UnPause() noexcept;

		bool IsPaused() const noexcept;

		virtual bool Initialize(int* argc, char* argv[]);

		virtual void Update() noexcept = 0;

		virtual void Draw() const noexcept = 0;

		virtual int Run() noexcept = 0;
	};

#if defined(_MSC_VER)
#  pragma comment(linker, "/ENTRY:mainCRTStartup")
#  if defined(_DEBUG)
#    pragma comment(linker, "/SUBSYSTEM:console ")
#    pragma message(__FILE__ ": /SUBSYSTEM:console /ENTRY:mainCRTStartup")
#  else
#    pragma comment(linker, "/SUBSYSTEM:windows")
#    pragma message(__FILE__ ": /SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#  endif
#endif
}

#endif //BLADE_APPLICATION_H_
