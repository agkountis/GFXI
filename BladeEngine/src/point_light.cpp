#include "point_light.h"

namespace Blade
{
	PointLight::PointLight(const std::string& name,
	                       const PointLightDesc& lightDescription)
		: Entity{ name }
	{
		m_PointLightComponent = new PointLightComponent{ lightDescription, this };

		m_PointLightComponent->Setup();
	}
}
