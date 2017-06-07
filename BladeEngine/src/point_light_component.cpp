#include "point_light_component.h"
#include "engine_context.h"

namespace Blade
{
	PointLightComponent::PointLightComponent(const struct PointLightDesc& lightDesc, Entity* parent)
		: LightComponent{ LightType::POINT, parent },
		m_LightDescription{ lightDesc }
	{
		G_LightSystem.RegisterComponent(this);
	}

	PointLightComponent::~PointLightComponent()
	{
		G_LightSystem.UnregisterComponent(GetId());
	}

	const PointLightDesc& PointLightComponent::GetLightDescription() const noexcept
	{
		return m_LightDescription;
	}

	PointLightDesc* PointLightComponent::GetLightDescriptionPtr() noexcept
	{
		return &m_LightDescription;
	}

}
