#include "entity.h"
#include "behaviour_system.h"
namespace Blade
{
	Entity::Entity(const std::string& name)
		: m_Name{ name },
		m_alive{ true },
		p_Parent{ nullptr }
	{
	}

	Entity::~Entity()
	{
		for (Component* component : m_Components)
		{
			delete component;
		}

		m_Components.clear();
	}

	Entity::Entity(const Entity& other)
		: ObserverSubject{ other },
		m_Components{ other.m_Components },
		m_Name{ other.m_Name },
		m_alive{ other.m_alive },
		m_Position{ other.m_Position },
		m_Orientation{ other.m_Orientation },
		m_Scale{ other.m_Scale },
		m_Xform{ other.m_Xform },
		p_Parent{ other.p_Parent }
	{
	}

	Entity& Entity::operator=(const Entity& other)
	{
		if (this == &other)
			return *this;
		ObserverSubject::operator =(other);
		m_Components = other.m_Components;
		m_Name = other.m_Name;
		m_alive = other.m_alive;
		m_Position = other.m_Position;
		m_Orientation = other.m_Orientation;
		m_Scale = other.m_Scale;
		m_Xform = other.m_Xform;
		p_Parent = other.p_Parent;
		return *this;
	}

	const std::string& Entity::GetName() const noexcept
	{
		return m_Name;
	}

	const Vec3f& Entity::GetPosition() const noexcept
	{
		return m_Position;
	}

	void Entity::SetPosition(const Vec3f& position) noexcept
	{
		m_Position = position;
	}

	const Quatf& Entity::GetOrientation() const noexcept
	{
		return m_Orientation;
	}

	void Entity::SetOrientation(const Quatf& orientation) noexcept
	{
		m_Orientation = orientation;
	}

	void Entity::SetOrientation(const Vec3f& axis, float angle) noexcept
	{
		Quatf q;
		m_Orientation = MathUtils::Rotate(q, angle, axis);
	}

	const Vec3f& Entity::GetScale() const noexcept
	{
		return m_Scale;
	}

	void Entity::SetScale(const Vec3f& scale) noexcept
	{
		m_Scale = scale;
	}

	Entity* Entity::GetParent() const noexcept
	{
		return p_Parent;
	}

	void Entity::SetParent(Entity* entity) noexcept
	{
		p_Parent = entity;
	}

	const Mat4f& Entity::GetXform() const noexcept
	{
		return m_Xform;
	}

	void Entity::SetXform(const Mat4f& xform) noexcept
	{
		m_Xform = xform;
	}

	void Entity::CalculateXform() noexcept
	{
		m_Xform = MathUtils::identityMatrix;

		m_Xform = MathUtils::Translate(m_Xform, m_Position);
		m_Xform = MathUtils::Rotate(m_Xform, m_Orientation);
		m_Xform = MathUtils::Scale(m_Xform, m_Scale);

		if (p_Parent) {
			m_Xform = p_Parent->GetXform() * m_Xform;
		}
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

	void Entity::AddComponent(Component* component) noexcept
	{
		m_Components.push_back(component);
	}

	bool Entity::IsAlive() const noexcept
	{
		return m_alive;
	}

	void Entity::SetAlive(bool state) noexcept
	{
		m_alive = state;
	}

	void Entity::Update(float dt, long time) noexcept
	{
		CalculateXform();
	}
}
