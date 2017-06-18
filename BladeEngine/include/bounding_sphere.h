#ifndef BLADE_BOUNDING_SPHERE
#define BLADE_BOUNDING_SPHERE
#include "collider.h"
#include "contact_manifold.h"

namespace Blade
{
	/**
	\brief BoundingSphere class of the engine is a Collider
	*/
	class BoundingSphere : public Collider
	{
	private:
		/**
		\brief The radius of the bounding sphere collider
		*/
		float m_Radius;

	public:
		explicit BoundingSphere(float radius);


		/**
		* \brief General method for collision detection with other collider.
		* \param collider Pointer to other collider.
		* \param manifold Reference to contact manifold to which the information about the collision will be added.
		* \remarks Other collider represents either BoundingSphere or PlaneCollider.
		* \return True if collision occured and entry was added to contact manifold, false otherwise
		*/
		bool Collide(const Collider* collider, ContactManifold& manifold) const noexcept override;


		/**
		* \brief Method for collision detection between this collider and Bounding Sphere collider.
		* \param bsphere Pointer to other collider - bounding sphere.
		* \param manifold Reference to contact manifold to which the information about the collision will be added.
		* \remarks Collision between two sphere colliders.
		* \return True if collision occured and entry was added to contact manifold, false otherwise
		*/
		bool Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept override;

		/**
		* \brief Method for collision detection between this collider and plane collider.
		* \param plane Pointer to other collider - plane colider.
		* \param manifold Reference to contact manifold to which the information about the collision will be added.
		* \remarks Collision between sphere and plane collider.
		* \return True if collision occured and entry was added to contact manifold, false otherwise
		*/
		bool Collide(const PlaneCollider* plane, ContactManifold& manifold) const noexcept override;


		/**
		* \brief Returns readius of the bounding sphere collider.
		* \return readius of the bounding sphere collider
		*/
		const float GetRadius() const noexcept;
	};
}
#endif