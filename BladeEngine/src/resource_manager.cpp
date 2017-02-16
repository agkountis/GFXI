#include "resource_manager.h"

namespace Blade
{
	std::map<std::wstring, Resource*> ResourceManager::m_ResourcesByName;

	std::map<unsigned int, Resource*> ResourceManager::m_ResourcesById;

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
