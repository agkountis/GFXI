#include "resource_manager.h"

namespace Blade
{
	ResourceManager::~ResourceManager()
	{
		for (auto resource : m_ResourcesByName)
		{
			delete resource.second;
		}

		m_ResourcesByName.clear();

		m_ResourcesById.clear();
	}
}
