#include "engine_context.h"
#include <iostream>
#include "trace.h"
namespace Blade
{
#if defined(BLADE_BUILD_D3D)
	std::unique_ptr<D3D11Context> EngineContext::m_GAPIContext{ std::make_unique<D3D11Context>() };

	D3D11Context* EngineContext::GetGAPIContext() noexcept
	{
		return m_GAPIContext.get();
	}
#else
#endif

	ThreadPool EngineContext::m_ThreadPool;

	// Systems
	RenderSystem EngineContext::m_RenderSystem;
	CameraSystem EngineContext::m_CameraSystem;
	LightSystem EngineContext::m_LightSystem;
	SimulationSystem EngineContext::m_SimulationSystem;
	BehaviourSystem EngineContext::m_BehaviourSystem;

	// Managers
	NetworkManager EngineContext::m_NetworkManager;
	RenderStateManager EngineContext::m_RenderStateManager;
	ResourceManager EngineContext::m_ResourceManager;
	SceneManager EngineContext::m_SceneManager;
	ShaderProgramManager EngineContext::m_ShaderProgramManager;

	bool EngineContext::Initialize()
	{
		if (!m_ThreadPool.Initialize())
		{
			BLADE_ERROR("Failed to initialize the thread pool.");
			return false;
		}

		if (!m_GAPIContext->Create())
		{
			BLADE_ERROR("Failed to initialize the engine's Graphics Context.");
			return false;
		}

		if (!m_RenderSystem.Initialize())
		{
			BLADE_ERROR("Failed to initialize the RenderSystem.");
			return false;
		}

		if (!m_SimulationSystem.Initialize())
		{
			BLADE_ERROR("Failed to initialize the SimulationSystem.");
			return false;
		}

		if (!m_BehaviourSystem.Initialize())
		{
			BLADE_ERROR("Failed to initialize the BehaviourSystem.");
			return false;
		}

		m_RenderStateManager.Initialize();

		if (!m_NetworkManager.Initialize())
		{
			BLADE_ERROR("Failed to initialize the NetworkManager.");
			return false;
		}

		return true;
	}

	ThreadPool& EngineContext::GetThreadPool() noexcept
	{
		return m_ThreadPool;
	}

	RenderSystem& EngineContext::GetRenderSystem() noexcept
	{
		return m_RenderSystem;
	}

	CameraSystem& EngineContext::GetCameraSystem() noexcept
	{
		return m_CameraSystem;
	}

	LightSystem& EngineContext::GetLightSystem() noexcept
	{
		return m_LightSystem;
	}

	SimulationSystem& EngineContext::GetSimulationSystem() noexcept
	{
		return m_SimulationSystem;
	}

	BehaviourSystem& EngineContext::GetBehaviourSystem() noexcept
	{
		return m_BehaviourSystem;
	}

	NetworkManager& EngineContext::GetNetworkManager() noexcept
	{
		return m_NetworkManager;
	}

	RenderStateManager& EngineContext::GetRenderStateManager() noexcept
	{
		return m_RenderStateManager;
	}

	ResourceManager& EngineContext::GetResourceManager() noexcept
	{
		return m_ResourceManager;
	}

	SceneManager& EngineContext::GetSceneManager() noexcept
	{
		return m_SceneManager;
	}

	ShaderProgramManager& EngineContext::GetShaderProgramManager() noexcept
	{
		return m_ShaderProgramManager;
	}
}
