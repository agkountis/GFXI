#ifndef BLADE_RENDER_SYSTEM_H_
#define BLADE_RENDER_SYSTEM_H_
#include "system.h"
#include <vector>
#include "render_pass.h"

namespace Blade
{
	class RenderSystem : public System
	{
	private:
		std::vector<RenderPass*> m_RenderPasses;
		
		std::vector<RenderComponent*> m_RenderComponents;
		
	public:
		void RegisterComponent(RenderComponent* renderComponent) noexcept;

		void UnregisterComponent(int id) noexcept;

		void AddRenderPass(RenderPass* renderPass) noexcept;

		void ClearRenderPasses() noexcept;

		bool Initialize() noexcept override;
		
		void Process(float deltaTime) noexcept override;
	};
}

#endif //BLADE_RENDER_SYSTEM_H_
