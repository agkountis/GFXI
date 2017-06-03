#ifndef BLADE_RENDER_STATE_MANAGER_H_
#define BLADE_RENDER_STATE_MANAGER_H_
#include <map>
#include "render_state.h"
#include <memory>

namespace Blade
{
	class RenderStateManager
	{
	private:
		std::map<RenderStateType, std::unique_ptr<RenderState>> m_RenderStates;

	public:
		void Initialize() noexcept;

		void Set(RenderStateType renderState) noexcept;
	};
}

#endif //BLADE_RENDER_STATE_MANAGER_H_
