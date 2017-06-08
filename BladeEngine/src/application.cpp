#include "application.h"
#include "engine_context.h"
#include <iostream>
#include "trace.h"

namespace Blade
{
	void Application::SetTermination(bool state) noexcept
	{
		m_Terminate = state;
	}

	bool Application::ShouldTerminate() const noexcept
	{
		return m_Terminate;
	}

	double Application::GetDelta() const noexcept
	{
		return m_Timer.GetDelta();
	}

	long Application::GetMsec() const noexcept
	{
		return m_Timer.GetMsec();
	}

	double Application::GetSec() const noexcept
	{
		return m_Timer.GetSec();
	}

	void Application::Pause() noexcept
	{
		m_Paused = true;
		m_Timer.Stop();
	}

	void Application::UnPause() noexcept
	{
		m_Paused = false;
		m_Timer.Start();
	}

	bool Application::IsPaused() const noexcept
	{
		return m_Paused;
	}

	void Application::SetLoadEntityCallback(const LoadEntityCallback& callback) noexcept
	{
		m_LoadEntityCallback = callback;
	}

	const LoadEntityCallback& Application::GetLoadEntityCallback() const noexcept
	{
		return m_LoadEntityCallback;
	}

	bool Application::Initialize(int* argc, char* argv[])
	{
		if (!EngineContext::Initialize())
		{
			BLADE_ERROR("Application initialization failed!");
			return false;
		}

		EngineContext::RegisterApplication(this);

		m_Timer.Start();

		return true;
	}
}
