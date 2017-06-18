#ifndef BLADE_RENDER_STATE_MANAGER_H_
#define BLADE_RENDER_STATE_MANAGER_H_
#include <map>
#include "render_state.h"
#include <memory>

namespace Blade
{
	/**
	\brief Render state manager of the engine. Stores render state types and provide 
	function to get and set those.
	*/
	class RenderStateManager
	{
	private:
		/**
		\brief Map that associate the render type to an unique render state.
		*/
		std::map<RenderStateType, std::unique_ptr<RenderState>> m_RenderStates;

	public:
		/**
		\brief Initialize the render state manager.
		*/
		void Initialize() noexcept;

		/**
		\brief Set the render state 
		\param renderState The render state to set.
		*/
		void Set(RenderStateType renderState) noexcept;
	};
}

#endif //BLADE_RENDER_STATE_MANAGER_H_
