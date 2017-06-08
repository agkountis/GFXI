#include "light_system.h"
#include "trace.h"
#include "entity.h"
#include "point_light_component.h"
#include "directional_light_component.h"
#include "spotlight_component.h"
#include "thread_pool.h"
#include "engine_context.h"

namespace Blade
{
	void LightSystem::RegisterComponent(LightComponent* lightComponent) noexcept
	{
		//Check if we reached the maximum amount of lights.
		if (m_LightComponents.size() < MAX_LIGHTS)
		{
			//Register the component to the map.
			m_LightComponents[lightComponent->GetParent()->GetName()] = lightComponent;

			//Get the LightType
			LightType type{ lightComponent->GetLightType() };

			//Determine in which cache the LightDescription will be placed.
			switch (type)
			{
			case LightType::POINT:
			{
				PointLightDesc* lightDescPtr{ static_cast<PointLightComponent*>(lightComponent)->GetLightDescriptionPtr() };

				//Make a tuple of the description and the LightComponent it belongs to.
				m_PointLightDescCache.push_back(std::make_tuple(lightDescPtr, lightComponent));

				//Set the index of the description in the cache to the component.
				lightComponent->SetLightDescCacheIndex(m_PointLightDescCache.size() - 1);

				BLADE_TRACE("Registered point light!");
			}
			break;

			case LightType::DIRECTIONAL:
			{
				DirectionalLightDesc* lightDescPtr{ static_cast<DirectionalLightComponent*>(lightComponent)->GetLightDescriptionPtr() };

				m_DirectionalLightDescCache.push_back(std::make_tuple(lightDescPtr, lightComponent));

				lightComponent->SetLightDescCacheIndex(m_DirectionalLightDescCache.size() - 1);

				BLADE_TRACE("Registered directional light!");
			}
			break;

			case LightType::SPOTLIGHT:
			{
				SpotlightDesc* lightDescPtr{ static_cast<SpotlightComponent*>(lightComponent)->GetLightDescriptionPtr() };

				m_SpotlightDescCache.push_back(std::make_tuple(lightDescPtr, lightComponent));

				lightComponent->SetLightDescCacheIndex(m_SpotlightDescCache.size() - 1);

				BLADE_TRACE("Registered spot light!");
			}
			break;
			}

			BLADE_TRACE("Registered LightComponent!");
		}
		else
		{
			BLADE_TRACE("Maximum amount of lights reached! LightComponent registration failed.");
		}
	}

	void LightSystem::UnregisterComponent(int id) noexcept
	{
		auto it{ m_LightComponents.begin() };

		//Iterate through all of the components.
		while (it != m_LightComponents.end())
		{
			auto entry{ *it };

			//If found
			if (entry.second->GetId() == id)
			{
				//Get the LightComponent from the map entry.
				LightComponent* component{ entry.second };

				//Get the cache index where it's LightDescription is located.
				int cacheIndex{ component->GetLightDescCacheIndex() };

				switch (component->GetLightType())
				{
				case LightType::POINT:
					//If the description is not in the end of the vector
					if (cacheIndex < m_PointLightDescCache.size() - 1)
					{
						//swap the last element with the one we want to remove. (We don't really care about the ordering and we avoid linear complexity)
						swap(m_PointLightDescCache[cacheIndex], m_PointLightDescCache.back());

						//After the swap get the moved element and update the LightComponent of the tuple with the new index of it's description.
						std::get<LightComponent*>(m_PointLightDescCache[cacheIndex])->SetLightDescCacheIndex(cacheIndex);
					}

					//If the description to be removed got swaped it gets removed. If the description was already in the end of the vector it gets removed.
					m_PointLightDescCache.pop_back();
					break;

				case LightType::DIRECTIONAL:
					if (cacheIndex < m_DirectionalLightDescCache.size() - 1)
					{
						swap(m_DirectionalLightDescCache[cacheIndex], m_DirectionalLightDescCache.back());

						std::get<LightComponent*>(m_DirectionalLightDescCache[cacheIndex])->SetLightDescCacheIndex(cacheIndex);
					}

					m_DirectionalLightDescCache.pop_back();
					break;

				case LightType::SPOTLIGHT:
					if (cacheIndex < m_SpotlightDescCache.size() - 1)
					{
						swap(m_SpotlightDescCache[cacheIndex], m_SpotlightDescCache.back());

						std::get<LightComponent*>(m_SpotlightDescCache[cacheIndex])->SetLightDescCacheIndex(cacheIndex);
					}

					m_SpotlightDescCache.pop_back();
					break;
				}

				//Erase the map entry.
				it = m_LightComponents.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	std::vector<PointLightDesc> LightSystem::GetPointLightDescriptions() const noexcept
	{
		std::vector<PointLightDesc> lightDescs;

		for (auto lightDescTuple : m_PointLightDescCache)
		{
			lightDescs.push_back(*std::get<PointLightDesc*>(lightDescTuple));
		}

		return std::move(lightDescs);
	}

	std::vector<DirectionalLightDesc> LightSystem::GetDirectionalLightDescriptions() const noexcept
	{
		std::vector<DirectionalLightDesc> lightDescs;

		for (auto lightDescTuple : m_DirectionalLightDescCache)
		{
			lightDescs.push_back(*std::get<DirectionalLightDesc*>(lightDescTuple));
		}

		return std::move(lightDescs);
	}

	std::vector<SpotlightDesc> LightSystem::GetSpotlightDescriptions() const noexcept
	{
		std::vector<SpotlightDesc> lightDescs;

		for (auto lightDescTuple : m_SpotlightDescCache)
		{
			lightDescs.push_back(*std::get<SpotlightDesc*>(lightDescTuple));
		}

		return std::move(lightDescs);
	}

	bool LightSystem::Initialize() noexcept
	{
		return true;
	}

	void LightSystem::Process(float deltaTime/*=.0f*/, long time/*=0*/) noexcept
	{
		G_ThreadPool.AddTask([this]() {

			for (auto entry : m_LightComponents)
			{
				LightComponent* lightComponent{ entry.second };

				LightType lightType{ lightComponent->GetLightType() };

				switch (lightType)
				{
				case LightType::POINT:
				{
					PointLightComponent* pointLightComponent{ static_cast<PointLightComponent*>(lightComponent) };
					pointLightComponent->GetLightDescriptionPtr()->position = pointLightComponent->GetParent()->GetPosition();
				}
				break;
				case LightType::DIRECTIONAL:
				{
					DirectionalLightComponent* directionalLightComponent{ static_cast<DirectionalLightComponent*>(lightComponent) };
					directionalLightComponent->GetLightDescriptionPtr()->direction = directionalLightComponent->GetParent()->GetPosition();
				}
				break;
				case LightType::SPOTLIGHT:
				{
					SpotlightComponent* spotlightComponent{ static_cast<SpotlightComponent*>(lightComponent) };
					spotlightComponent->GetLightDescriptionPtr()->position = spotlightComponent->GetParent()->GetPosition();
				}
				break;
				}
			}
		});
	}
}
