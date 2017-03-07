#include "directional_light_component.h"

namespace Blade
{
	DirectionalLightComponent::DirectionalLightComponent(const struct DirectionalLightDesc& lightDesc, Entity* parent)
		: LightComponent{ LightType::DIRECTIONAL, parent },
		m_LightDescription{ lightDesc }
	{
	}

	const DirectionalLightDesc& DirectionalLightComponent::GetLightDescription() const noexcept
	{
		return m_LightDescription;
	}

	DirectionalLightDesc* DirectionalLightComponent::GetLightDescriptionPtr() noexcept
	{
		return &m_LightDescription;
	}
}
