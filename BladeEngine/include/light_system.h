#ifndef BLADE_LIGHT_SYSTEM_H_
#define BLADE_LIGHT_SYSTEM_H_
#include "system.h"
#include <map>
#include "light_component.h"
#include <vector>

namespace Blade
{
	/**
	 * \brief Max number of lights supported by the engine.
	 */
	static const int MAX_LIGHTS = 10;

	using PointLightDescTuple = std::tuple<PointLightDesc*, LightComponent*>;

	using DirectionalLightDescTuple = std::tuple<DirectionalLightDesc*, LightComponent*>;

	using SpotlightDescTuple = std::tuple<SpotlightDesc*, LightComponent*>;

	/**
	 * \brief A System responsible for managing LightComponents.
	 * This system updates the positions of all the lights in the scene every frame.
	 * It is also responsible for caching the light descriptions of each light upon registration of
	 * a LightConponent.
	 */
	class LightSystem : public System
	{
	private:
		/**
		 * \brief A map of LightComponents using a string identifier as the key.
		 */
		std::map<std::string, LightComponent*> m_LightComponents;

		/**
		 * \brief A vector used as a chache for all the active point light descriptions.
		 * \details This vector caches all the point light descriptions in the form of a tuple
		 * that contains a pointer to a PointLightDesc struct
		 * and a pointer to the LightComponent that owns the PointLightDesc struct.
		 */
		std::vector<PointLightDescTuple> m_PointLightDescCache;

		/**
		* \brief A vector used as a chache for all the active directional light descriptions.
		* \details This vector caches all the directional light descriptions in the form of a tuple
		* that contains a pointer to a DirectionalLightDesc struct
		* and a pointer to the LightComponent that owns the DirectionalLightDesc struct.
		*/
		std::vector<DirectionalLightDescTuple> m_DirectionalLightDescCache;

		/**
		* \brief A vector used as a chache for all the active spotlight descriptions.
		* \details This vector caches all the point light descriptions in the form of a tuple
		* that contains a pointer to a SpotlightDesc struct
		* and a pointer to the LightComponent that owns the SpotlightDesc struct.
		*/
		std::vector<SpotlightDescTuple> m_SpotlightDescCache;

	public:
		/**
		 * \brief Registers a LightComponent to the system.
		 * \details This method registers a LightComponent to the system.
		 * It maps the LightComponent with a name and based on it's type it puts the light description
		 * contained in the LightComponent to the correct light description cache.
		 * \param lightComponent The LightComponent to be registered.
		 */
		void RegisterComponent(LightComponent* lightComponent) noexcept;

		/**
		 * \brief Unregisters a LightComponent from the system.
		 * \details This method unregisters a LightComponent and based on it's type removes
		 * it's light description from the correct light description cache.
		 * \param id The id of the LightComponent to unregister.
		 */
		void UnregisterComponent(int id) noexcept;

		/**
		 * \brief Provides a vector of the cached point light description structs.
		 * \return A vector of the cached point light description structs.
		 */
		std::vector<PointLightDesc> GetPointLightDescriptions() const noexcept;

		/**
		 * \brief Provides a vector of the cached directional light description structs.
		 * \return A vector of the cached directional light description structs.
		 */
		std::vector<DirectionalLightDesc> GetDirectionalLightDescriptions() const noexcept;

		/**
		 * \brief Provides a vector of the chached spotlight description structs.
		 * \return A vector of the cached spotlight description structs.
		 */
		std::vector<SpotlightDesc> GetSpotlightDescriptions() const noexcept;

		bool Initialize() noexcept override;

		/**
		 * \brief Processes the LightComponents.
		 * \details This method iterates through all the active LightComponents. Based on their
		 * type it updates the position/direction data members of each LightComponent's
		 * light description contained in the matching cache.
		 * \param deltaTime The time elapsed from the previous frame of the application.
		 */
		void Process(float deltaTime = 0) noexcept override;
	};
}

#endif //BLADE_LIGHT_SYSTEM_H_
