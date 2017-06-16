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
#include "audio_manager.h"

#ifdef BLADE_BUILD_OVR
#include "ovr_manager.h"
#endif

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
		static AudioManager m_AudioManager;

#ifdef BLADE_BUILD_OVR
		static OvrManager m_OvrManager;
#endif

	public:
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

		static AudioManager& GetAudioManager() noexcept;

#ifdef BLADE_BUILD_OVR
		static OvrManager& GetOvrManager() noexcept;
#endif
	};

#define G_GAPIContext Blade::EngineContext::GetGAPIContext()

#define G_ThreadPool Blade::EngineContext::GetThreadPool()

#define G_RenderSystem Blade::EngineContext::GetRenderSystem()
#define G_CameraSystem Blade::EngineContext::GetCameraSystem()
#define G_LightSystem Blade::EngineContext::GetLightSystem()
#define G_SimulationSystem Blade::EngineContext::GetSimulationSystem()
#define G_BehaviourSystem Blade::EngineContext::GetBehaviourSystem()

#define G_NetworkManager Blade::EngineContext::GetNetworkManager()
#define G_RenderStateManager Blade::EngineContext::GetRenderStateManager()
#define G_ResourceManager Blade::EngineContext::GetResourceManager()
#define G_SceneManager Blade::EngineContext::GetSceneManager()
#define G_ShaderProgramManager Blade::EngineContext::GetShaderProgramManager()
#define G_InputManager Blade::EngineContext::GetInputManager()
#define G_ParticleSystem Blade::EngineContext::GetParticleSystem()
#define G_Application Blade::EngineContext::GetApplication()
#define G_AudioManager Blade::EngineContext::GetAudioManager()

#ifdef BLADE_BUILD_OVR
#define G_OvrManager Blade::EngineContext::GetOvrManager()
#endif
}

#endif //BLADE_CONTEXT_H_
