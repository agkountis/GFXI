#ifndef BLADE_ENTITY_H_
#define BLADE_ENTITY_H_
#include <vector>
#include "component.h"
#include "types.h"
#include "math_utils.h"
#include "observer_subject.h"

namespace Blade
{
	class Entity : public ObserverSubject
	{
	private:
		std::vector<Component*> m_Components;

		std::string m_Name;

		bool m_alive;

		Vec3f m_Position;
		Quatf m_Orientation;
		Vec3f m_Scale{ 1.0f, 1.0f, 1.0f };

		Mat4f m_Xform;

		Entity* p_Parent;

	public:
		explicit Entity(const std::string& name)
			: m_Name{ name },
			  m_alive{ true },
			  p_Parent{ nullptr }
		{
		}

		~Entity();


		Entity(const Entity& other)
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

		Entity& operator=(const Entity& other)
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

		const std::string& GetName() const noexcept
		{
			return m_Name;
		}

		const Vec3f& GetPosition() const noexcept
		{
			return m_Position;
		}

		void SetPosition(const Vec3f& position) noexcept
		{
			m_Position = position;
		}

		const Quatf& Entity::GetOrientation() const noexcept
		{
			return m_Orientation;
		}

		void SetOrientation(const Quatf& orientation) noexcept
		{
			m_Orientation = orientation;
		}

		void SetOrientation(const Vec3f& axis, float angle) noexcept
		{
			Quatf q;
			m_Orientation = MathUtils::Rotate(q, angle, axis);
		}

		const Vec3f& GetScale() const noexcept
		{
			return m_Scale;
		}

		void SetScale(const Vec3f& scale) noexcept
		{
			m_Scale = scale;
		}

		Entity* GetParent() const noexcept
		{
			return p_Parent;
		}

		void SetParent(Entity* entity) noexcept
		{
			p_Parent = entity;
		}

		const Mat4f& GetXform() const noexcept
		{
			return m_Xform;
		}

		void SetXform(const Mat4f& xform) noexcept
		{
			m_Xform = xform;
		}

		void CalculateXform() noexcept
		{
			m_Xform = MathUtils::identityMatrix;

			m_Xform = MathUtils::Translate(m_Xform, m_Position);
			m_Xform = MathUtils::Rotate(m_Xform, m_Orientation);
			m_Xform = MathUtils::Scale(m_Xform, m_Scale);

			if (p_Parent) {
				m_Xform = p_Parent->GetXform() * m_Xform;
			}
		}

		Component* GetComponent(const std::string& type) const noexcept;

		void AddComponent(Component* component) noexcept
		{
			m_Components.push_back(component);
		}

		bool IsAlive() const noexcept
		{
			return m_alive;
		}
		
		void SetAlive(bool state) noexcept
		{
			m_alive = state;
		}

		virtual void Update(float dt, long time = 0) noexcept;
	};
}

#endif //BLADE_ENTITY_H_
