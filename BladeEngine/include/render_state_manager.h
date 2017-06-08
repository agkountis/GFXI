#ifndef BLADE_RENDER_STATE_MANAGER_H_
#define BLADE_RENDER_STATE_MANAGER_H_
#include <map>
#include "render_state.h"
#include <memory>

namespace Blade
{
	/*
	\brief Render state manager of the engine.
	*/
	class RenderStateManager
	{
	private:
		/*
		\brief Map that associate the render type to an unique render state.
		*/
		std::map<RenderStateType, std::unique_ptr<RenderState>> m_RenderStates;

	public:
		void Initialize() noexcept;

		void Set(RenderStateType renderState) noexcept;
	};
}

#endif //BLADE_RENDER_STATE_MANAGER_H_
