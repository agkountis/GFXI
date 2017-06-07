#ifndef BLADE_RESOURCE_MANAGER_H_
#define BLADE_RESOURCE_MANAGER_H_
#include <map>
#include <iostream>
#include "resource.h"

namespace Blade
{
	static const std::wstring MODELS_PATH{ L"data\\models\\" };
	static const std::wstring TEXTURE_PATH{ L"data\\textures\\" };

	static int s_Id = 0;

	/*
	\brief Resource manager class of the engine.
	*/
	class ResourceManager
	{
	private:
		/*
		\brief Correlate resource by names.
		*/
		std::map<std::wstring, Resource*> m_ResourcesByName;

		/*
		\brief Correlate resources by indices.
		*/
		std::map<unsigned int, Resource*> m_ResourcesById;

	public:
		~ResourceManager();

		template <typename T>
		/*
		\brief Load a new resource by file name
		\return true if the resource is loaded correctly,
		false otherwise.
		*/
		bool Load(const std::wstring& fileName)
		{
			T* resource{ new T };

			if (resource->Load(fileName))
			{
				resource->SetId(s_Id);
				RegisterResource(resource, fileName);

				return true;
			}

			return false;
		}

		/*
		\brief Get a resource by name
		\return the resource
		*/
		template <typename T>
		T* Get(const std::wstring& fileName)
		{
			Resource* resource{ m_ResourcesByName[fileName] };

			if (!resource)
			{
				Load<T>(fileName);
				resource = m_ResourcesByName[fileName];
			}

			T* res{ dynamic_cast<T*>(resource) };
			if (!res)
			{
				std::cerr << "The file you asked for does not represent the type you are requesting!" << std::endl;
				return nullptr;
			}

			return res;
		}

		/*
		\brief Register a new resource by name
		\param resource the resource to register
		\name the name of the resource.
		*/
		void RegisterResource(Resource* resource, const std::wstring& name)
		{
			if (!resource)
			{
				std::cerr << "Resource registration failed: Cannot register a null resource." << std::endl;
				return;
			}

			if (name.empty())
			{
				std::cerr << "Resource registration failed: Cannot register a resource without providing a name." << std::endl;
				return;
			}

			m_ResourcesByName[name] = resource;
			m_ResourcesById[s_Id++] = resource;
		}
	};
}

#endif //BLADE_RESOURCE_MANAGER_H_
