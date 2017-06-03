#include  "spotlight.h"

namespace Blade
{
	Spotlight::Spotlight(const std::string& name,
	                     const SpotlightDesc& lightDescription)
		: Entity{ name }
	{
		m_SpotlightComponent = new SpotlightComponent{ lightDescription, this };

		m_SpotlightComponent->Setup();
	}
}
