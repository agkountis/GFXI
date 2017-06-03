#ifndef BLADE_POINT_LIGHT_COMPONENT_H_
#define BLADE_POINT_LIGHT_COMPONENT_H_
#include "light_component.h"

namespace Blade
{
	class PointLightComponent : public LightComponent
	{
	private:
		PointLightDesc m_LightDescription;

	public:
		PointLightComponent(const PointLightDesc& lightDesc, Entity* parent);

		~PointLightComponent();

		const PointLightDesc& GetLightDescription() const noexcept;

		PointLightDesc* GetLightDescriptionPtr() noexcept;

	};
}

#endif //BLADE_POINT_LIGHT_COMPONENT_H_

