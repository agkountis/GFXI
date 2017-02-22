#ifndef BLADE_RENDER_PASS_H_
#define BLADE_RENDER_PASS_H_
#include <vector>
#include "render_component.h"

namespace Blade
{
	class RenderPass
	{
	private:
		std::string m_Name;

	public:
		RenderPass(const std::string& name)
			: m_Name{ name }
		{
		}

		virtual ~RenderPass() = default;

		virtual bool Initialize() = 0;

		virtual void Execute(const std::vector<RenderComponent*>& renderComponents) const noexcept = 0;
	};
}

#endif //BLADE_RENDER_PASS_H_
