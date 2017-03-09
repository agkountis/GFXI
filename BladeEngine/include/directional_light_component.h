#ifndef BLADE_DIRECTIONAL_LIGHT_COMPONENT_H_
#define BLADE_DIRECTIONAL_LIGHT_COMPONENT_H_
#include "light_component.h"

namespace Blade
{
	class DirectionalLightComponent : public LightComponent
	{
	private:
		DirectionalLightDesc m_LightDescription;

	public:
		DirectionalLightComponent(const DirectionalLightDesc& lightDesc, Entity* parent);

		~DirectionalLightComponent();

		const DirectionalLightDesc& GetLightDescription() const noexcept;

		DirectionalLightDesc* GetLightDescriptionPtr() noexcept;

		void Setup() noexcept override;
		
		void Update(float dt, long time) noexcept override;
		
		void Teardown() noexcept override;
	};
}

#endif //BLADE_DIRECTIONAL_LIGHT_COMPONENT_H_
