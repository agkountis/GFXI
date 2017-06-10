#include "engine_context.h"
#include <iostream>
#include "trace.h"
namespace Blade
{
#if defined(BLADE_BUILD_D3D)
	D3D11Context EngineContext::m_GAPIContext;

	D3D11Context& EngineContext::GetGAPIContext() noexcept
	{
		return m_GAPIContext;
	}
#else
#endif

	Application* EngineContext::m_pApplication{ nullptr };

	ThreadPool EngineContext::m_ThreadPool;

	// Systems
	RenderSystem EngineContext::m_RenderSystem;
	CameraSystem EngineContext::m_CameraSystem;
	LightSystem EngineContext::m_LightSystem;
	BehaviourSystem EngineContext::m_BehaviourSystem;
	SimulationSystem EngineContext::m_SimulationSystem;
	ParticleSystem EngineContext::m_ParticleSystem;


	// Managers
	NetworkManager EngineContext::m_NetworkManager;
	RenderStateManager EngineContext::m_RenderStateManager;
	ResourceManager EngineContext::m_ResourceManager;
	SceneManager EngineContext::m_SceneManager;
	ShaderProgramManager EngineContext::m_ShaderProgramManager;
	InputManager EngineContext::m_InputManager;

	bool EngineContext::Initialize()
	{
		if (!m_ThreadPool.Initialize())
		{
			BLADE_ERROR("Failed to initialize the thread pool.");
			return false;
		}

		if (!m_GAPIContext.Create(nullptr))
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

		if (!m_ParticleSystem.Initialize())
		{
			BLADE_ERROR("Failed to initialize the ParticleSytem.");
			return false;
		}

		m_RenderStateManager.Initialize();

		if (!m_NetworkManager.Initialize())
		{
			BLADE_ERROR("Failed to initialize the NetworkManager.");
			return false;
		}

		if (!m_InputManager.Initialize())
		{
			BLADE_ERROR("Failed to initialize the Input system.");
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

	ParticleSystem & EngineContext::GetParticleSystem() noexcept
	{
		return m_ParticleSystem;
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

	InputManager& EngineContext::GetInputManager() noexcept
	{
		return m_InputManager;
	}

	void EngineContext::RegisterApplication(Application* application) noexcept
	{
		m_pApplication = application;
	}

	Application& EngineContext::GetApplication() noexcept
	{
		return *m_pApplication;
	}
}
