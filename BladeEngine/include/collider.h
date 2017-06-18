#ifndef BLADE_COLLIDER_H_
#define BLADE_COLLIDER_H_
#include "contact_manifold.h"

namespace Blade
{
	//Forward declarations
	class ColliderComponent;
	class BoundingSphere;
	class PlaneCollider;

	/**
	\brief This class represents a general collider.
	*/
	class Collider
	{
	private:
		/**
		\brief Holds the pointer to the correspondent collider component
		*/
		ColliderComponent* m_Parent{ nullptr };



	public:
		Collider() = default;

		virtual ~Collider() = default;


		/**
		* \brief Interface method for collision detection with other collider.
		* \param collider Pointer to other collider. 
		* \param manifold Reference to contact manifold to which the information about the collision will be added.
		* \remarks Other collider represents either BoundingSphere or PlaneCollider.
		* \return True if collision occured and entry was added to contact manifold, false otherwise
		*/
		virtual bool Collide(const Collider* collider, ContactManifold& manifold) const noexcept = 0;


		/**
		* \brief Interface method for collision detection between this collider and Bounding Sphere collider.
		* \param bsphere Pointer to other collider - bounding sphere.
		* \param manifold Reference to contact manifold to which the information about the collision will be added.
		* \return True if collision occured and entry was added to contact manifold, false otherwise
		*/
		virtual bool Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept = 0;


		/**
		* \brief Interface method  for collision detection between this collider and plane collider.
		* \param plane Pointer to other collider - plane colider.
		* \param manifold Reference to contact manifold to which the information about the collision will be added.
		* \return True if collision occured and entry was added to contact manifold, false otherwise
		*/
		virtual bool Collide(const PlaneCollider* plane, ContactManifold& manifold) const noexcept = 0;



		/**
		* \brief Returns the pointer to correspondent collider component
		* \return the pointer to correspondent collider component
		*/
		ColliderComponent* GetColliderComponent() const noexcept { return m_Parent; };



		/**
		* \brief Sets correspondent collider component of this collider.
		* \param colliderComponent Corresponding collider component to be set and used.
		*/
		void SetParent(ColliderComponent* colliderComponent) noexcept { m_Parent = colliderComponent; };
	};

}


#endif