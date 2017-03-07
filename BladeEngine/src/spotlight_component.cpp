#include "spotlight_component.h"

namespace Blade
{
	SpotlightComponent::SpotlightComponent(const struct SpotlightDesc& lightDesc, Entity* parent)
		: LightComponent{ LightType::SPOTLIGHT, parent },
		m_LightDescription{ lightDesc }
	{
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
