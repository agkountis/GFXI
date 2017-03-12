#ifndef BLADE_LIGHT_SYSTEM_H_
#define BLADE_LIGHT_SYSTEM_H_
#include "system.h"
#include <map>
#include "light_component.h"
#include <vector>

namespace Blade
{
	static const int MAX_LIGHTS = 10;

	using PointLightDescTuple = std::tuple<PointLightDesc*, LightComponent*>;

	using DirectionalLightDescTuple = std::tuple<DirectionalLightDesc*, LightComponent*>;

	using SpotlightDescTuple = std::tuple<SpotlightDesc*, LightComponent*>;

	class LightSystem : public System
	{
	private:
		std::map<std::string, LightComponent*> m_LightComponents;

		std::vector<PointLightDescTuple> m_PointLightDescCache;

		std::vector<DirectionalLightDescTuple> m_DirectionalLightDescCache;

		std::vector<SpotlightDescTuple> m_SpotlightDescCache;

	public:
		void RegisterComponent(LightComponent* lightComponent) noexcept;

		void UnregisterComponent(int id) noexcept;

		std::vector<PointLightDesc> GetPointLightDescriptions() const noexcept;

		std::vector<DirectionalLightDesc> GetDirectionalLightDescriptions() const noexcept;

		std::vector<SpotlightDesc> GetSpotlightDescriptions() const noexcept;

		bool Initialize() noexcept override;

		void Process(float deltaTime = 0) noexcept override;
	};
}

#endif //BLADE_LIGHT_SYSTEM_H_
