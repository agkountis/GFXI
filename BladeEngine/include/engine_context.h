#ifndef BLADE_CONTEXT_H_
#define BLADE_CONTEXT_H_
#include "d3d/D3D11_context.h"
#include "render_system.h"
#include "camera_system.h"
#include "light_system.h"
#include "simulation_system.h"

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
		//TODO: Declare all the systems as statics here

	public:
		EngineContext() = default;

		EngineContext(const EngineContext& context) = delete;

		EngineContext& operator=(const EngineContext& context) = delete;

		static bool Initialize();

#if defined(BLADE_BUILD_D3D)
		static D3D11Context* get_GAPI_context() noexcept;
#else
#endif
		static RenderSystem* GetRenderSystem() noexcept;

		static CameraSystem* GetCameraSystem() noexcept;

		static LightSystem* GetLightSystem() noexcept;

		static SimulationSystem* GetSimulationSystem() noexcept;
		//TODO: Implement getters and setters for the systems.
	};
}

#endif //BLADE_CONTEXT_H_
