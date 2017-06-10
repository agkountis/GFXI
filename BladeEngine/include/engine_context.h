#ifndef BLADE_CONTEXT_H_
#define BLADE_CONTEXT_H_
#include "d3d/D3D11_context.h"
#include "render_system.h"
#include "camera_system.h"
#include "light_system.h"
#include "simulation_system.h"
#include "behaviour_system.h"
#include "thread_pool.h"
#include "network_manager.h"
#include "render_state_manager.h"
#include "resource_manager.h"
#include "scene_manager.h"
#include "shader_program_manager.h"
#include "particle_system.h"
#include "input_manager.h"
#include <OVR/OVR_CAPI.h>

namespace Blade
{
	class Application;

	/*
	\brief The engine context class stores all the system of the engines and
	the application. It defines an unique and reliable access to all the sub-models
	of the engine.
	*/
	class EngineContext
	{
	private:
#if defined(BLADE_BUILD_D3D)
		static D3D11Context m_GAPIContext;
#else
#endif
		static Application* m_pApplication;

		static ThreadPool m_ThreadPool;

		// Systems
		static RenderSystem m_RenderSystem;
		static CameraSystem m_CameraSystem;
		static LightSystem m_LightSystem;
		static SimulationSystem m_SimulationSystem;
		static BehaviourSystem m_BehaviourSystem;
		static ParticleSystem m_ParticleSystem;

		// Managers
		static NetworkManager m_NetworkManager;
		static RenderStateManager m_RenderStateManager;
		static ResourceManager m_ResourceManager;
		static SceneManager m_SceneManager;
		static ShaderProgramManager m_ShaderProgramManager;
		static InputManager m_InputManager;

	public:
		static ovrSession session;
		static ovrGraphicsLuid graphicsLuid;

		EngineContext() = default;

		EngineContext(const EngineContext& context) = delete;

		EngineContext& operator=(const EngineContext& context) = delete;

		static bool Initialize();

#if defined(BLADE_BUILD_D3D)
		static D3D11Context& GetGAPIContext() noexcept;
#else
#endif
		static ThreadPool& GetThreadPool() noexcept;

		static RenderSystem& GetRenderSystem() noexcept;

		static CameraSystem& GetCameraSystem() noexcept;

		static LightSystem& GetLightSystem() noexcept;

		static SimulationSystem& GetSimulationSystem() noexcept;

		static BehaviourSystem& GetBehaviourSystem() noexcept;

		static NetworkManager& GetNetworkManager() noexcept;

		static RenderStateManager& GetRenderStateManager() noexcept;

		static ResourceManager& GetResourceManager() noexcept;

		static SceneManager& GetSceneManager() noexcept;

		static ShaderProgramManager& GetShaderProgramManager() noexcept;

		static InputManager& GetInputManager() noexcept;

		static ParticleSystem& GetParticleSystem() noexcept;

		static void RegisterApplication(Application* application) noexcept;

		static Application& GetApplication() noexcept;
	};

#define G_GAPIContext EngineContext::GetGAPIContext()

#define G_ThreadPool EngineContext::GetThreadPool()

#define G_RenderSystem EngineContext::GetRenderSystem()
#define G_CameraSystem EngineContext::GetCameraSystem()
#define G_LightSystem EngineContext::GetLightSystem()
#define G_SimulationSystem EngineContext::GetSimulationSystem()
#define G_BehaviourSystem EngineContext::GetBehaviourSystem()

#define G_NetworkManager EngineContext::GetNetworkManager()
#define G_RenderStateManager EngineContext::GetRenderStateManager()
#define G_ResourceManager EngineContext::GetResourceManager()
#define G_SceneManager EngineContext::GetSceneManager()
#define G_ShaderProgramManager EngineContext::GetShaderProgramManager()
#define G_InputManager EngineContext::GetInputManager()
#define G_ParticleSystem EngineContext::GetParticleSystem()
#define G_Application EngineContext::GetApplication()
}

#endif //BLADE_CONTEXT_H_
