#include "application.h"
#include <iostream>

namespace Blade
{
	EngineContext Application::m_EngineContext;

	Application::~Application()
	{
	}


	bool Application::Initialize(int* argc, char* argv[])
	{
		if (!m_EngineContext.Initialize())
		{
			std::cerr << "Application initialization failed!" << std::endl;
			return false;
		}

		m_timer.Start();

		return true;
	}
}
