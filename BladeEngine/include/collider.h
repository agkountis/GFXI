#ifndef BLADE_COLLIDER_H_
#define BLADE_COLLIDER_H_
#include "contact_manifold.h"

namespace Blade
{
	//Forward declarations
	class ColliderComponent;
	class BoundingSphere;

	/*
	\brief This class represents a general collider. 
	*/
	class Collider
	{
	private:
		/*
		\brief Holds the pointer to the correspondent collider component
		*/
		ColliderComponent* m_Parent{ nullptr };

	public:
		Collider() = default;

		virtual ~Collider() = default;

		virtual bool Collide(const Collider* collider, ContactManifold& manifold) const noexcept = 0;

		virtual bool Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept = 0;

		ColliderComponent* GetColliderComponent() const noexcept { return m_Parent; };

		void SetParent(ColliderComponent* cc) noexcept { m_Parent = cc; };
	};

}


#endif