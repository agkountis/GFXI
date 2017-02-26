#ifndef BLADE_RENDER_SYSTEM_H_
#define BLADE_RENDER_SYSTEM_H_
#include "system.h"
#include <vector>
#include "pipeline.h"

namespace Blade
{
	class RenderSystem : public System
	{
	private:
		RenderPassPipeline* m_RenderPassPipeline{ nullptr };
		
		std::vector<RenderComponent*> m_RenderComponents;
		
	public:
		~RenderSystem();

		void RegisterComponent(RenderComponent* renderComponent) noexcept;

		void UnregisterComponent(int id) noexcept;

		void SetRenderPassPipeline(RenderPassPipeline* renderPassPipeline) noexcept;

		void ClearRenderPassPipeline() noexcept;

		bool Initialize() noexcept override;
		
		void Process(float deltaTime = 0) noexcept override;
	};
}

#endif //BLADE_RENDER_SYSTEM_H_
