#include "render_system.h"

namespace Blade
{
	void RenderSystem::RegisterComponent(RenderComponent* renderComponent) noexcept
	{
		m_RenderComponents.push_back(renderComponent);
	}

	void RenderSystem::UnregisterComponent(int id) noexcept
	{
		std::remove_if(m_RenderComponents.begin(),
		               m_RenderComponents.end(),
		               [id](RenderComponent* component)
		               {
			               return id == component->GetId();
		               }
		);
	}

	void RenderSystem::AddRenderPass(RenderPass* renderPass) noexcept
	{
		m_RenderPasses.push_back(renderPass);
	}

	void RenderSystem::ClearRenderPasses() noexcept
	{
		for (auto renderPass : m_RenderPasses)
		{
			delete renderPass;
		}

		m_RenderPasses.clear();
	}

	bool RenderSystem::Initialize() noexcept
	{
		return true;
	}

	void RenderSystem::Process(float deltaTime) noexcept
	{
		for (auto renderPass : m_RenderPasses)
		{
			renderPass->Execute(m_RenderComponents);
		}
	}
}
