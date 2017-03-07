#include "point_light_component.h"

namespace Blade
{
	PointLightComponent::PointLightComponent(const struct PointLightDesc& lightDesc, Entity* parent)
		: LightComponent{ LightType::POINT, parent },
		m_LightDescription{ lightDesc }
	{
	}

	const PointLightDesc& PointLightComponent::GetLightDescription() const noexcept
	{
		return m_LightDescription;
	}

	PointLightDesc* PointLightComponent::GetLightDescriptionPtr() noexcept
	{
		return &m_LightDescription;
	}

	void PointLightComponent::Setup() noexcept
	{
	}

	void PointLightComponent::Update(float dt, long time) noexcept
	{
	}

	void PointLightComponent::Teardown() noexcept
	{
	}
}
