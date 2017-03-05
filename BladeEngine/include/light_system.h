#ifndef BLADE_LIGHT_SYSTEM_H_
#define BLADE_LIGHT_SYSTEM_H_
#include "system.h"
#include <map>
#include "light_component.h"
#include <vector>

namespace Blade
{
	static const int MAX_LIGHTS = 10;

	class LightSystem : public System
	{
	private:
		std::map<std::string, LightComponent*> m_LightComponents;

		std::vector<PointLightDesc*> m_PointLightDescCache;

		std::vector<DirectionalLightDesc*> m_DirectionalLightDescCache;

		std::vector<SpotLightDesc*> m_SpotLightDescCache;

		bool m_PointLightDescCacheValid{ true };
		
		bool m_DirectionalDescLightCacheValid{ true };
		
		bool m_SpotLightDescCacheValid{ true };

	public:
		void RegisterComponent(LightComponent* lightComponent) noexcept;

		void UnregisterComponent(int id) noexcept;

		bool Initialize() noexcept override;

		void Process(float deltaTime = 0) noexcept override;
	};
}

#endif //BLADE_LIGHT_SYSTEM_H_
