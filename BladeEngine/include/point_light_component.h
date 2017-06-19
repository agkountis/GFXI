#ifndef BLADE_POINT_LIGHT_COMPONENT_H_
#define BLADE_POINT_LIGHT_COMPONENT_H_
#include "light_component.h"

namespace Blade
{
	/**
	 * \brief Point light implementation of the LightComponent.
	 */
	class PointLightComponent : public LightComponent
	{
	private:
		PointLightDesc m_LightDescription;

	public:
		PointLightComponent(const PointLightDesc& lightDesc, Entity* parent);

		~PointLightComponent();

		/**
		 * \brief Returns the description of the point light.
		 * \return The description of the point light.
		 */
		const PointLightDesc& GetLightDescription() const noexcept;

		/**
		 * \brief Returns a pointer to the description of the point light.
		 * \return A pointer to the description of the point light.
		 */
		PointLightDesc* GetLightDescriptionPtr() noexcept;
	};
}

#endif //BLADE_POINT_LIGHT_COMPONENT_H_

