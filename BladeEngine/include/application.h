#ifndef BLADE_APPLICATION_H_
#define BLADE_APPLICATION_H_
#include "engine_context.h"
#include "timer.h"

namespace Blade
{

	using LoadEntityCallback = std::function<bool(const std::wstring& fileName, Entity* thisObject)>;

	/**
	\brief Application class of the engine
	*/
	class Application
	{
	private:

		/**
		\brief Terminate flag
		*/
		bool m_Terminate{ false };

		/**
		\brief Paused flag
		*/
		bool m_Paused{ false };

		/**
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

		/**
		\brief Set the termination flag 
		\param state The state of the application to set.
		*/
		void SetTermination(bool state) noexcept;

		/**
		\brief Return the should terminate flag
		\return TRUE if the application should terminate, false otherwise
		*/
		bool ShouldTerminate() const noexcept;

		/**
		\brief Get the delta time of the application.
		\return The delta time.
		*/
		double GetDelta() const noexcept;

		/**
		\brief Get the time elapse since the startup in milliseconds
		\return time elapsed in milliseconds 
		*/
		long GetMsec() const noexcept;

		/**
		\brief Get the time elapsed since the startup in seconds 
		\return time elapsed in seconds. 
		*/
		double GetSec() const noexcept;

		/**
		\brief Pause the application.
		*/
		void Pause() noexcept;

		/**
		\brief Un pause the application.
		*/
		void UnPause() noexcept;

		/**
		\brief Check if the application is paused
		\return TRUE if the application is paused, FALSE otherwise
		*/
		bool IsPaused() const noexcept;

		/**
		\brief Set the load entity call back 
		\param callback The callback used to load entities from file.
		*/
		void SetLoadEntityCallback(const LoadEntityCallback& callback) noexcept;

		/**
		\brief Get the load entity call back of the engine
		\return The callback used to load entities.
		*/
		const LoadEntityCallback& GetLoadEntityCallback() const noexcept;

		/**
		\brief Initialize the application
		*/
		virtual bool Initialize(int* argc, char* argv[]);

		/**
		\brief Update the application
		*/
		virtual void Update() noexcept = 0;

		/**
		\brief Draw the application on screen.
		*/
		virtual void Draw() const noexcept = 0;

		/**
		\brief Run the application.
		*/
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
