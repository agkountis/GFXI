#include "directional_light.h"

namespace Blade
{
	DirectionalLight::DirectionalLight(const std::string& name,
	                                   const DirectionalLightDesc& lightDescription)
		: Entity{ name }
	{
		m_DirectionalLightComponent = new DirectionalLightComponent{ lightDescription, this };

		m_DirectionalLightComponent->Setup();
	}
}
