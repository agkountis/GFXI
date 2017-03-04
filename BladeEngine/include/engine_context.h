#ifndef BLADE_CONTEXT_H_
#define BLADE_CONTEXT_H_
#include "d3d/D3D11_context.h"
#include "render_system.h"
#include "camera_system.h"

namespace Blade
{
	class EngineContext
	{
	private:
#if defined(BLADE_BUILD_D3D)
		static D3D11Context* m_GAPIContext;
#else
#endif
		static std::unique_ptr<RenderSystem> m_RenderSystem;
		static std::unique_ptr<CameraSystem> m_CameraSystem;
		//TODO: Declare all the systems as statics here

	public:
		EngineContext() = default;
		~EngineContext();

		EngineContext(const EngineContext& context) = delete;

		EngineContext& operator=(const EngineContext& context) = delete;

		static bool Initialize();

#if defined(BLADE_BUILD_D3D)
		static D3D11Context* get_GAPI_context() noexcept
		{
			return m_GAPIContext;
		}
#endif
		static RenderSystem* GetRenderSystem() noexcept;

		static CameraSystem* GetCameraSystem() noexcept;
		//TODO: Implement getters and setters for the systems.
	};
}

#endif //BLADE_CONTEXT_H_
