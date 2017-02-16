#include "engine_context.h"
#include "d3d/D3D11_context.h"
#include <iostream>
#include "render_state_manager.h"

namespace Blade
{
#if defined(BLADE_BUILD_D3D)
	D3D11Context* EngineContext::mGAPIContext{ nullptr };
#else
#endif


	EngineContext::~EngineContext()
	{
		delete mGAPIContext;
	}

	bool EngineContext::Initialize()
	{
#if defined(GLACIERENGINE_BUILD_D3D)
		m_GAPI_context = new D3D11Context;
#else
		//Allocate GL context
#endif
		if (!mGAPIContext->Create())
		{
			std::cerr << "Failed to initialize the engine's Graphics Context!" << std::endl;
			return false;
		}

		//TODO: Initialise the systems here

		RenderStateManager::Initialize();

		return true;
	}
}
