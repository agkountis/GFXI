#include "engine_context.h"
#include "d3d/D3D11_context.h"
#include <iostream>
#include "render_state_manager.h"

namespace Blade
{
	std::unique_ptr<ThreadPool> EngineContext::m_ThreadPool{ std::make_unique<ThreadPool>() };

#if defined(BLADE_BUILD_D3D)
	std::unique_ptr<D3D11Context> EngineContext::m_GAPIContext{ std::make_unique<D3D11Context>() };

	D3D11Context* EngineContext::GetGAPIContext() noexcept
	{
		return m_GAPIContext.get();
	}
#else
#endif

	std::unique_ptr<RenderSystem> EngineContext::m_RenderSystem{ std::make_unique<RenderSystem>() };
	std::unique_ptr<CameraSystem> EngineContext::m_CameraSystem{ std::make_unique<CameraSystem>() };
	std::unique_ptr<LightSystem> EngineContext::m_LightSystem{ std::make_unique<LightSystem>() };
	std::unique_ptr<SimulationSystem> EngineContext::m_SimulationSystem{ std::make_unique<SimulationSystem>() };

	bool EngineContext::Initialize()
	{
		if (!m_ThreadPool->Initialize())
		{
			std::cerr << "Failed to initialize the thread pool." << std::endl;
			return false;
		}

		if (!m_GAPIContext->Create())
		{
			std::cerr << "Failed to initialize the engine's Graphics Context." << std::endl;
			return false;
		}

		if (!m_RenderSystem->Initialize())
		{
			std::cerr << "Failed to initialize the RenderSystem." << std::endl;
			return false;
		}

		if (!m_SimulationSystem->Initialize())
		{
			std::cerr << "Failed to initialize the SimulationSystem." << std::endl;
			return false;
		}

		RenderStateManager::Initialize();

		return true;
	}

	RenderSystem* EngineContext::GetRenderSystem() noexcept
	{
		return m_RenderSystem.get();
	}

	CameraSystem* EngineContext::GetCameraSystem() noexcept
	{
		return m_CameraSystem.get();
	}

	LightSystem* EngineContext::GetLightSystem() noexcept
	{
		return m_LightSystem.get();
	}

	SimulationSystem * EngineContext::GetSimulationSystem() noexcept
	{
		return m_SimulationSystem.get();
	}

	ThreadPool* EngineContext::GetThreadPool() noexcept
	{
		return m_ThreadPool.get();
	}
}
