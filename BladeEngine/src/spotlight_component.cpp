#include "spotlight_component.h"
#include "engine_context.h"

namespace Blade
{
	SpotlightComponent::SpotlightComponent(const struct SpotlightDesc& lightDesc, Entity* parent)
		: LightComponent{ LightType::SPOTLIGHT, parent },
		  m_LightDescription{ lightDesc }
	{
		G_LightSystem.RegisterComponent(this);
	}

	SpotlightComponent::~SpotlightComponent()
	{
		G_LightSystem.UnregisterComponent(GetId());
	}

	const SpotlightDesc& SpotlightComponent::GetLightDescription() const noexcept
	{
		return m_LightDescription;
	}

	SpotlightDesc* SpotlightComponent::GetLightDescriptionPtr() noexcept
	{
		return &m_LightDescription;
	}

}
