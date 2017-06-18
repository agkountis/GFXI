#ifndef BLADE_DIRECTIONAL_LIGHT_H_
#define BLADE_DIRECTIONAL_LIGHT_H_
#include "entity.h"
#include "light_component.h"
#include "directional_light_component.h"

namespace Blade
{
	/**
	* \brief DirectionalLight class of the engine.
	*  Object used to generate directional light in the scene
	*/
	class DirectionalLight : public Entity
	{
	private:
		DirectionalLightComponent* m_DirectionalLightComponent{ nullptr };

	public:
		/**
		* \brief Creates new instance of the light object.
		* \param name Name of the light to be created.
		* \param lightDescription Description structure of the light.
		*/
		DirectionalLight(const std::string& name, const DirectionalLightDesc& lightDescription);
	};
}

#endif //BLADE_DIRECTIONAL_LIGHT_H_
