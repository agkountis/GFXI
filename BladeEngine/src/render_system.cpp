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
		auto it{ m_RenderComponents.begin() };

		while (it != m_RenderComponents.end())
		{
			auto entry{ *it };
			if (entry->GetId() == id)
			{
				it = m_RenderComponents.erase(it);
			}
			else
			{
				++it;
			}
		}

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

	void RenderSystem::Process(float deltaTime/*=.0f*/, long time/*=0*/) noexcept
	{
		m_RenderPassPipeline->Execute(m_RenderComponents);
	}
}
