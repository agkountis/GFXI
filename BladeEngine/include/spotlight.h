#ifndef BLADE_SPOTLIGHT_H_
#define BLADE_SPOTLIGHT_H_
#include "entity.h"
#include "spotlight_component.h"

namespace Blade
{
	class Spotlight : public Entity
	{
	private:
		SpotlightComponent* m_SpotlightComponent{ nullptr };

	public:
		Spotlight(const std::string& name, const SpotlightDesc& lightDescription);
	};
}

#endif //BLADE_SPOTLIGHT_H_
