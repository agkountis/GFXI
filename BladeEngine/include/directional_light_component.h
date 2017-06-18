#ifndef BLADE_DIRECTIONAL_LIGHT_COMPONENT_H_
#define BLADE_DIRECTIONAL_LIGHT_COMPONENT_H_
#include "light_component.h"

namespace Blade
{
	/**
	* \brief Component used to generate directional light in the scene.
	*/
	class DirectionalLightComponent : public LightComponent
	{
	private:
		DirectionalLightDesc m_LightDescription;

	public:
		/**
		* \brief Creates new instance of Directional light component.
		* \param lightDescription Description structure of the light to be created.
		* \param parent Pointer to parent entity of the component.
		*/
		DirectionalLightComponent(const DirectionalLightDesc& lightDescription, Entity* parent);

		~DirectionalLightComponent();

		/**
		* \brief Returns light description structure of the light component.
		* \return Light description structure of the light component.
		*/
		const DirectionalLightDesc& GetLightDescription() const noexcept;

		/**
		* \brief Returns pointer to light description structure of the light component.
		* \return Pointer to light description structure of the light component.
		*/
		DirectionalLightDesc* GetLightDescriptionPtr() noexcept;
	};
}

#endif //BLADE_DIRECTIONAL_LIGHT_COMPONENT_H_
