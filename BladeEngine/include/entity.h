#ifndef BLADE_ENTITY_H_
#define BLADE_ENTITY_H_
#include <vector>
#include "component.h"
#include "types.h"
#include "math_utils.h"
#include "observer_subject.h"

namespace Blade
{
	/*
	\brief Entity class of the engine
	\details An entity stores a collection of components, has a unique name and 
	its own transform matrix.
	*/
	class Entity : public ObserverSubject
	{
	private:
		/*
		\brief The vector of the components attached to the entity.
		*/
		std::vector<Component*> m_Components;

		/*
		\brief Name of the entity
		*/
		std::string m_Name;

		/*
		\brief Alive flag of the entity
		\details if is false the entity won't be updated.
		*/
		bool m_alive;

		/*
		\brief Entity position in world coordinates
		*/
		Vec3f m_Position;

		/*
		\brief Entity orientation.
		*/
		Quatf m_Orientation;

		/*
		\brief Entity scale
		\details Not uniform scaling is permitted. 
		*/
		Vec3f m_Scale{ 1.0f, 1.0f, 1.0f };

		/*
		\brief Transform matrix of the entity
		*/
		Mat4f m_Xform;

		/*
		\brief Pointer to the parent of the entity
		\details This can be used to create a parent child relationship between
		entities. This means that if, for example a child entity, will take in consideration
		the parent transform matrix.
		*/
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

		/*
		\brief Calculate the transformation matrix of the entity
		\details If the entity has a parent, the transformation matrix 
		is multiplied by the transformation matrix of his parent.
		*/
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

		/*
		\brief Return a component that is attached to the entity.
		*/
		Component* GetComponent(const std::string& type) const noexcept;

		/*
		\brief Attach a new component to the entity.
		*/
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

		/*
		\brief Update the entity transformation matrix.
		*/
		virtual void Update(float dt, long time = 0) noexcept;
	};
}

#endif //BLADE_ENTITY_H_
