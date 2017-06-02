#ifndef BLADE_SPOTLIGHT_COMPONENT_H_
#define BLADE_SPOTLIGHT_COMPONENT_H_
#include "light_component.h"

namespace Blade
{
	class SpotlightComponent : public LightComponent
	{
	private:
		SpotlightDesc m_LightDescription;

	public:
		SpotlightComponent(const SpotlightDesc& lightDesc, Entity* parent);

		~SpotlightComponent();

		const SpotlightDesc& GetLightDescription() const noexcept;

		SpotlightDesc* GetLightDescriptionPtr() noexcept;

		void Setup() noexcept override;

		void Update(float dt, long time) noexcept override;
		
		void Teardown() noexcept override;
	};
}

#endif //BLADE_SPOTLIGHT_COMPONENT_H_
