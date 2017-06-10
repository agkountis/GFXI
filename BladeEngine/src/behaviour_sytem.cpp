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
		for (auto i{ 0 };i<m_BehaviourComponents.size();++i)
		{
			m_BehaviourComponents[i]->Update(deltaTime,time);
		}
	}


	void BehaviourSystem::RegisterComponent(BehaviourComponent* behaviourComponent) noexcept
	{
		m_BehaviourComponents.push_back(behaviourComponent);
	}

	void BehaviourSystem::UnregisterComponent(int id) noexcept
	{
		auto it{ m_BehaviourComponents.begin() };

		while (it != m_BehaviourComponents.end())
		{
			auto entry{ *it };
			if (entry->GetId() == id)
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
		for (auto behaviour : m_BehaviourComponents)
		{
			behaviour->Setup();
		}
	}

	void BehaviourSystem::Teardown() noexcept
	{
		for (auto behaviour : m_BehaviourComponents)
		{
			behaviour->Teardown();
		}
	}

}
