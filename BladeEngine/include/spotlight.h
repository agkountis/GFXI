#ifndef BLADE_SPOTLIGHT_H_
#define BLADE_SPOTLIGHT_H_
#include "entity.h"
#include "spotlight_component.h"

namespace Blade
{
	/**
	* \brief Spotlight class of the engine.
	*  Object used to generate spotlight in the scene.
	*/
	class Spotlight : public Entity
	{
	private:
		SpotlightComponent* m_SpotlightComponent{ nullptr };

	public:
		/**
		* \brief Creates new instance of the light object.
		* \param name Name of the light to be created.
		* \param lightDescription Description structure of the light.
		*/
		Spotlight(const std::string& name, const SpotlightDesc& lightDescription);
	};
}

#endif //BLADE_SPOTLIGHT_H_
