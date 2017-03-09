#include "spotlight_component.h"
#include "engine_context.h"

namespace Blade
{
	SpotlightComponent::SpotlightComponent(const struct SpotlightDesc& lightDesc, Entity* parent)
		: LightComponent{ LightType::SPOTLIGHT, parent },
		  m_LightDescription{ lightDesc }
	{
		EngineContext::GetLightSystem()->RegisterComponent(this);
	}

	SpotlightComponent::~SpotlightComponent()
	{
		EngineContext::GetLightSystem()->UnregisterComponent(GetId());
	}

	const SpotlightDesc& SpotlightComponent::GetLightDescription() const noexcept
	{
		return m_LightDescription;
	}

	SpotlightDesc* SpotlightComponent::GetLightDescriptionPtr() noexcept
	{
		return &m_LightDescription;
	}

	void SpotlightComponent::Setup() noexcept
	{
	}

	void SpotlightComponent::Update(float dt, long time) noexcept
	{
	}

	void SpotlightComponent::Teardown() noexcept
	{
	}
}
