#include "behaviour_system.h"
#include "entity.h"
#include <iostream>

namespace Blade
{
	bool BehaviourSystem::Initialize() noexcept
	{
		return true;
	}

	void BehaviourSystem::Process(float deltaTime/*=.0f*/, long time/*=0*/) noexcept
{
		for (auto pair : m_BehaviourComponents)
		{
			auto component{ pair.second };
			component->Update(deltaTime,time);
		}
	}


	void BehaviourSystem::RegisterComponent(BehaviourComponent* behaviourComponent) noexcept
	{
		m_BehaviourComponents[behaviourComponent->GetParent()->GetName()] = behaviourComponent;
	}

	void BehaviourSystem::UnregisterComponent(int id) noexcept
	{
		auto it{ m_BehaviourComponents.begin() };

		while (it != m_BehaviourComponents.end())
		{
			auto entry{ *it };
			if (entry.second->GetId() == id)
			{
				it = m_BehaviourComponents.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void BehaviourSystem::Setup() noexcept
	{
		for (auto pair : m_BehaviourComponents)
		{
			auto behaviour{ pair.second };
			behaviour->Setup();
		}
	}

	void BehaviourSystem::Teardown() noexcept
	{
		for (auto pair : m_BehaviourComponents)
		{
			auto behaviour{ pair.second };
			behaviour->Teardown();
		}
	}
	std::vector<BehaviourComponent*>& BehaviourSystem::GetBehaviourByType(const std::string type)
	{
		std::vector<BehaviourComponent*>  result;

		for (auto entry : m_BehaviourComponents)
		{
			if (entry.first == type)
			{
				result.push_back(entry.second);
			}
		}
		return std::move(result);
	}
}
