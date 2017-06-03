#ifndef BLADE_DIRECTIONAL_LIGHT_H_
#define BLADE_DIRECTIONAL_LIGHT_H_
#include "entity.h"
#include "light_component.h"
#include "directional_light_component.h"

namespace Blade
{
	class DirectionalLight : public Entity
	{
	private:
		DirectionalLightComponent* m_DirectionalLightComponent{ nullptr };

	public:
		DirectionalLight(const std::string& name, const DirectionalLightDesc& lightDescription);
	};
}

#endif //BLADE_DIRECTIONAL_LIGHT_H_
