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
	}

	
}
