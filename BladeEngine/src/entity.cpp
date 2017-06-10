#include "entity.h"
#include "behaviour_system.h"
#include "trace.h"
#include "engine_context.h"
#include "application.h"

namespace Blade
{
	Entity::Entity(const std::string& name)
		: m_Name{ name },
		  m_Alive{ true },
		  m_pParent{ nullptr }
	{
	}

	Entity::~Entity()
	{
		for (Component* component : m_Components)
		{
			delete component;
		}


		m_Components.clear();

		for (auto child : m_Children)
		{
			delete child;
		}

		m_Children.clear();
	}

	Entity::Entity(const Entity& other)
		: ObserverSubject{ other },
		  m_Components{ other.m_Components },
		  m_Name{ other.m_Name },
		  m_Alive{ other.m_Alive },
		  m_Position{ other.m_Position },
		  m_Orientation{ other.m_Orientation },
		  m_Scale{ other.m_Scale },
		  m_Xform{ other.m_Xform },
		  m_pParent{ other.m_pParent }
	{
	}

	Entity& Entity::operator=(const Entity& other)
	{
		if (this == &other)
			return *this;
		ObserverSubject::operator =(other);
		m_Components = other.m_Components;
		m_Name = other.m_Name;
		m_Alive = other.m_Alive;
		m_Position = other.m_Position;
		m_Orientation = other.m_Orientation;
		m_Scale = other.m_Scale;
		m_Xform = other.m_Xform;
		m_pParent = other.m_pParent;
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
		return m_pParent;
	}

	void Entity::SetParent(Entity* entity) noexcept
	{
		m_pParent = entity;
	}

	const std::vector<Entity*>& Entity::GetChildren() const noexcept
	{
		return m_Children;
	}

	Entity* Entity::GetChild(int index) const noexcept
	{
		return m_Children[index];
	}

	void Entity::AddChild(Entity* entity) noexcept
	{
		entity->SetParent(this);

		m_Children.push_back(entity);
	}

	size_t Entity::GetChildrenCount() const noexcept
	{
		return m_Children.size();
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

		if (m_pParent)
		{
			m_Xform = m_pParent->GetXform() * m_Xform;
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

	std::vector<Component*> Entity::GetComponents(const std::string & type) const noexcept
	{
		std::vector<Component*> result;
		for (const auto component : m_Components)
		{
			if (component->GetType() == type)
			{
				result.push_back(component);
			}
		}

		return result;
	}

	void Entity::AddComponent(Component* component) noexcept
	{
		m_Components.push_back(component);
	}

	bool Entity::IsAlive() const noexcept
	{
		return m_Alive;
	}

	void Entity::SetAlive(bool state) noexcept
	{
		m_Alive = state;
	}

	void Entity::Update(float dt, long time) noexcept
	{
		CalculateXform();

		for (auto child : m_Children)
		{
			child->Update(dt, time);
		}
	}

	bool Entity::Load(const std::wstring& fileName) noexcept
	{
		auto& callback = G_Application.GetLoadEntityCallback();
		if (callback)
		{
			return callback(fileName, this);
		}

		BLADE_ERROR("Call to Load but no load callback provided");
		return false;
	}
}
