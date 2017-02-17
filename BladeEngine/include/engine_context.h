#ifndef BLADE_CONTEXT_H_
#define BLADE_CONTEXT_H_

#include "d3d/D3D11_context.h"

namespace Blade
{
	class EngineContext
	{
	private:
#if defined(BLADE_BUILD_D3D)
		static D3D11Context* m_GAPIContext;
#else
#endif
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

		//TODO: Implement getters and setters for the systems.
	};
}

#endif //BLADE_CONTEXT_H_
