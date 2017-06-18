#ifndef BLADE_POINT_LIGHT_H_
#define BLADE_POINT_LIGHT_H_
#include "entity.h"
#include "point_light_component.h"

namespace Blade
{
	/**
	* \brief PointLight class of the engine.
	*  Object used to generate point light in the scene
	*/
	class PointLight : public Entity
	{
	private:
		PointLightComponent* m_PointLightComponent{ nullptr };

	public:
		/**
		* \brief Creates new instance of the light object.
		* \param name Name of the light to be created.
		* \param lightDescription Description structure of the light.
		*/
		PointLight(const std::string& name, const PointLightDesc& lightDescription);
	};
}

#endif //BLADE_POINT_LIGHT_H_
