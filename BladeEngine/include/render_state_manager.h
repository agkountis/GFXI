#ifndef BLADE_RENDER_STATE_MANAGER_H_
#define BLADE_RENDER_STATE_MANAGER_H_
#include <map>
#include "render_state.h"

namespace Blade
{
	class RenderStateManager
	{
	private:
		static std::map<RenderStateType, RenderState*> m_RenderStates;

	public:
		RenderStateManager();

		~RenderStateManager();

		RenderStateManager(const RenderStateManager&) = delete;

		RenderStateManager& operator=(const RenderStateManager&) = delete;

		static void Initialize() noexcept;

		static void Set(RenderStateType renderState) noexcept;
	};
}

#endif //BLADE_RENDER_STATE_MANAGER_H_
