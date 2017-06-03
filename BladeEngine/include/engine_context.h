#ifndef BLADE_CONTEXT_H_
#define BLADE_CONTEXT_H_
#include "d3d/D3D11_context.h"
#include "render_system.h"
#include "camera_system.h"
#include "light_system.h"
#include "simulation_system.h"
#include "behaviour_system.h"
#include "input_manager.h"
#include "thread_pool.h"
namespace Blade
{
	class EngineContext
	{
	private:
#if defined(BLADE_BUILD_D3D)
		static std::unique_ptr<D3D11Context> m_GAPIContext;
#else
#endif
		static std::unique_ptr<RenderSystem> m_RenderSystem;
		static std::unique_ptr<CameraSystem> m_CameraSystem;
		static std::unique_ptr<LightSystem> m_LightSystem;
		static std::unique_ptr<SimulationSystem> m_SimulationSystem;
		static std::unique_ptr<BehaviourSystem> m_BehaviourSystem;
		static std::unique_ptr<InputManager> m_InputManager;
		//TODO: Declare all the systems as statics here

	public:
		EngineContext() = default;

		EngineContext(const EngineContext& context) = delete;

		EngineContext& operator=(const EngineContext& context) = delete;

		static bool Initialize();

#if defined(BLADE_BUILD_D3D)
		static D3D11Context* GetGAPIContext() noexcept;
#else
#endif
		static RenderSystem* GetRenderSystem() noexcept;

		static CameraSystem* GetCameraSystem() noexcept;

		static LightSystem* GetLightSystem() noexcept;

		static SimulationSystem* GetSimulationSystem() noexcept;

		static BehaviourSystem* GetBehaviourSystem() noexcept;

		static InputManager*	GetInputManager() noexcept;
	};
}

#endif //BLADE_CONTEXT_H_
