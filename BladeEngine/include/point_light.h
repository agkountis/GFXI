#ifndef BLADE_POINT_LIGHT_H_
#define BLADE_POINT_LIGHT_H_
#include "entity.h"
#include "point_light_component.h"

namespace Blade
{
	class PointLight : public Entity
	{
	private:
		PointLightComponent* m_PointLightComponent{ nullptr };

	public:
		PointLight(const std::string& name, const PointLightDesc& lightDescription);
	};
}

#endif //BLADE_POINT_LIGHT_H_
