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

		static EngineContext m_EngineContext;

		Timer m_timer;

	public:
		Application() = default;
		Application(const Application& application) = delete;
		Application& operator=(const Application& application) = delete;

		virtual ~Application();

		void SetTermination(bool state) noexcept
		{
			m_Terminate = state;
		}

		bool ShouldTerminate() const noexcept
		{
			return m_Terminate;
		}

		double GetDelta() const noexcept
		{
			return m_timer.GetDelta();
		}

		long GetMsec() const noexcept
		{
			return m_timer.GetMsec();
		}

		double GetSec() const noexcept
		{
			return m_timer.GetSec();
		}

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
