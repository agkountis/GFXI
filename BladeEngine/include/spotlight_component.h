#ifndef BLADE_SPOTLIGHT_COMPONENT_H_
#define BLADE_SPOTLIGHT_COMPONENT_H_
#include "light_component.h"

namespace Blade
{
	/**
	* \brief SpotlightComponent class of the engine.
	*  Component used to generate spotlight in the scene
	*/
	class SpotlightComponent : public LightComponent
	{
	private:
		SpotlightDesc m_LightDescription;

	public:
		/**
		* \brief Creates new instance of spotlight component. 
		* \param lightDescription Description structure of the light to be created.
		* \param parent Pointer to parent entity of the component.
		*/
		SpotlightComponent(const SpotlightDesc& lightDescription, Entity* parent);

		~SpotlightComponent();

		/**
		* \brief Returns light description structure of the light component.
		* \return Light description structure of the light component.
		*/
		const SpotlightDesc& GetLightDescription() const noexcept;


		/**
		* \brief Returns pointer to light description structure of the light component.
		* \return Pointer to light description structure of the light component.
		*/
		SpotlightDesc* GetLightDescriptionPtr() noexcept;
	};
}

#endif //BLADE_SPOTLIGHT_COMPONENT_H_
