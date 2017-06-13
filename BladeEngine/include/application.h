#ifndef BLADE_APPLICATION_H_
#define BLADE_APPLICATION_H_
#include "engine_context.h"
#include "timer.h"

namespace Blade
{

	using LoadEntityCallback = std::function<bool(const std::wstring& fileName, Entity* thisObject)>;

	/*
	\brief Application class of the engine
	*/
	class Application
	{
	private:
		/*
		\brief Terminate flag
		*/
		bool m_Terminate{ false };

		/*
		\brief Paused flag
		*/
		bool m_Paused{ false };

		/*
		\brief Timer of the application used to propagate delta time and
		other time information to the systems.
		*/
		Timer m_Timer;

		LoadEntityCallback m_LoadEntityCallback;

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

		void SetLoadEntityCallback(const LoadEntityCallback& callback) noexcept;

		const LoadEntityCallback& GetLoadEntityCallback() const noexcept;

		virtual bool Initialize(int* argc, char* argv[]);

		virtual void Update() noexcept = 0;

		virtual void Draw() const noexcept = 0;

		virtual int Run() noexcept = 0;
	};

//#if defined(_MSC_VER)
//#  pragma comment(linker, "/ENTRY:mainCRTStartup")
//#  if defined(_DEBUG)
//#    pragma comment(linker, "/SUBSYSTEM:console ")
//#    pragma message(__FILE__ ": /SUBSYSTEM:console /ENTRY:mainCRTStartup")
//#  else
//#    pragma comment(linker, "/SUBSYSTEM:windows")
//#    pragma message(__FILE__ ": /SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//#  endif
//#endif
}

#endif //BLADE_APPLICATION_H_
