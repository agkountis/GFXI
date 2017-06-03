#include "entity.h"
#include "behaviour_system.h"
namespace Blade
{
	Entity::~Entity()
	{
		for (Component* component : m_Components)
		{
			delete component;
		}

		m_Components.clear();
	}

	Component* Entity::GetComponent(const std::string& type) const noexcept
	{
		for (const auto component : m_Components)
		{
			if (component->GetType() == type)
			{
				return component;
			}
		}

		return nullptr;
	}

	void Entity::Update(float dt, long time) noexcept
	{
		CalculateXform();

		for (auto component : m_Components)
		{
			auto behaviourComponent = dynamic_cast<BehaviourComponent*>(component);
			if (behaviourComponent != nullptr)
			{
				behaviourComponent->Update(dt, time);
			}
		}
	}

	void Entity::Setup() noexcept
	{
		for (auto component : m_Components)
		{
			auto behaviourComponent = dynamic_cast<BehaviourComponent*>(component);
			if (behaviourComponent != nullptr)
			{
			behaviourComponent->Setup();
			}
		}
	}

	void Entity::Teardown() noexcept
	{
		for (auto component : m_Components)
		{
			auto behaviourComponent = dynamic_cast<BehaviourComponent*>(component);
			if (behaviourComponent != nullptr)
			{
				behaviourComponent->Teardown();
			}
		}
	}
}
