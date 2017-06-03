#include "behaviour_system.h"
#include "entity.h"
#include <iostream>

namespace Blade
{
	bool BehaviourSystem::Initialize() noexcept
	{
		return true;
	}

	void BehaviourSystem::Process(float deltaTime) noexcept
	{
		for (auto pair : m_BehaviourComponents)
		{
			auto component{ pair.second };
			component->Update(deltaTime);
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
}
