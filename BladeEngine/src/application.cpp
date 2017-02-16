#include "application.h"
#include "engine_context.h"
#include <iostream>

namespace Blade
{
	Application::~Application()
	{
	}


	bool Application::Initialize(int* argc, char* argv[])
	{
		if (!EngineContext::Initialize())
		{
			std::cerr << "Application initialization failed!" << std::endl;
			return false;
		}

		m_Timer.Start();

		return true;
	}
}
