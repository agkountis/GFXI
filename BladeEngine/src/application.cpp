#include "application.h"
#include "engine_context.h"
#include <iostream>

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
