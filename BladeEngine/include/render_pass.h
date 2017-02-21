#ifndef BLADE_RENDER_PASS_H_
#define BLADE_RENDER_PASS_H_
#include <vector>
#include "render_component.h"

namespace Blade
{
	class RenderPass
	{
	public:
		virtual ~RenderPass() = default;

		virtual void Execute(const std::vector<RenderComponent*>& renderComponents) const noexcept = 0;
	};
}

#endif //BLADE_RENDER_PASS_H_
