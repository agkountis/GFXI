#include "render_system.h"

namespace Blade
{
	RenderSystem::~RenderSystem()
	{
		delete m_RenderPassPipeline;
	}

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

	void RenderSystem::SetRenderPassPipeline(RenderPassPipeline* renderPass) noexcept
	{
		if (m_RenderPassPipeline)
		{
			delete m_RenderPassPipeline;
			m_RenderPassPipeline = renderPass;
		}
		else
		{
			m_RenderPassPipeline = renderPass;
		}
	}

	void RenderSystem::ClearRenderPassPipeline() noexcept
	{
		if (m_RenderPassPipeline)
		{
			delete m_RenderPassPipeline;
			m_RenderPassPipeline = nullptr;
		}
	}

	bool RenderSystem::Initialize() noexcept
	{
		return true;
	}

	void RenderSystem::Process(float deltaTime) noexcept
	{
		m_RenderPassPipeline->Execute(m_RenderComponents);
	}
}
