#include "light_system.h"
#include "trace.h"
#include "entity.h"

namespace Blade
{
	void LightSystem::RegisterComponent(LightComponent* lightComponent) noexcept
	{
		if (m_LightComponents.size() < MAX_LIGHTS)
		{
			m_LightComponents[lightComponent->GetParent()->GetName()] = lightComponent;

			LightType type{ lightComponent->GetLightType() };

			switch (type)
			{
			case LightType::POSITIONAL:
			{
				PointLightDesc* lightDescPtr{ static_cast<PointLightComponent*>(lightComponent)->GetLightDescriptionPtr() };
				m_PointLightDescCache.push_back(lightDescPtr);
				lightComponent->SetLightDescCacheIndex(m_PointLightDescCache.size() - 1);
				BLADE_TRACE("Registered point light!")
			}
				break;
			case LightType::DIRECTIONAL:
			{
				DirectionalLightDesc* lightDescPtr{ static_cast<DirectionalLightComponent*>(lightComponent)->GetLightDescriptionPtr() };
				m_DirectionalLightDescCache.push_back(lightDescPtr);
				lightComponent->SetLightDescCacheIndex(m_DirectionalLightDescCache.size() - 1);
				BLADE_TRACE("Registered directional light!")
			}
				break;
			case LightType::SPOTLIGHT:
			{
				SpotLightDesc* lightDescPtr{ static_cast<SpotLightComponent*>(lightComponent)->GetLightDescriptionPtr() };
				m_SpotLightDescCache.push_back(lightDescPtr);
				lightComponent->SetLightDescCacheIndex(m_SpotLightDescCache.size() - 1);
				BLADE_TRACE("Registered spot light!")
			}
				break;
			}

			BLADE_TRACE("Registered LightComponent!")
		}
		else
		{
			BLADE_TRACE("Maximum amount of lights reached! LightComponent registration failed.")
		}
	}

	void LightSystem::UnregisterComponent(int id) noexcept
	{
		auto it{ m_LightComponents.begin() };

		while (it != m_LightComponents.end())
		{
			auto entry{ *it };
			if (entry.second->GetId() == id)
			{
				LightComponent* component{ entry.second };

				switch (component->GetLightType())
				{
				case LightType::POSITIONAL:
					if (component->GetLightDescCacheIndex() < m_PointLightDescCache.size() - 1)
					{
						swap(m_PointLightDescCache[component->GetLightDescCacheIndex()], m_PointLightDescCache.back());
					}

					m_PointLightDescCache.pop_back();
					break;
				case LightType::DIRECTIONAL:
					if (component->GetLightDescCacheIndex() < m_DirectionalLightDescCache.size() - 1)
					{
						swap(m_DirectionalLightDescCache[component->GetLightDescCacheIndex()], m_DirectionalLightDescCache.back());
					}

					m_DirectionalLightDescCache.pop_back();
					break;
				case LightType::SPOTLIGHT:
					if (component->GetLightDescCacheIndex() < m_SpotLightDescCache.size() - 1)
					{
						swap(m_SpotLightDescCache[component->GetLightDescCacheIndex()], m_SpotLightDescCache.back());
					}

					m_SpotLightDescCache.pop_back();
					break;
				}

				it = m_LightComponents.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	bool LightSystem::Initialize() noexcept
	{
	}

	void LightSystem::Process(float deltaTime) noexcept
	{
	}
}
