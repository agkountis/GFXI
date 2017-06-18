#ifndef BLADE_BOUNDING_PLANE_H_
#define BLADE_BOUNDING_PLANE_H_
#include "collider.h"
#include "contact_manifold.h"

namespace Blade
{
	/**
	* \brief Bounding Plane class is a collider
	*/
	class PlaneCollider : public Collider
	{
	private:
		/**
		\brief The plane normal
		*/
		Vec3f m_PlaneNormal;

		/**
		* \brief The distance of the plane from the origin
		*/
		float m_Offset;

	public:

		explicit PlaneCollider(const Vec3f& planeNormal, const float offset);


		/**
		* \brief General method for collision detection with other collider.
		* \param collider Pointer to other collider.
		* \param manifold Reference to contact manifold, to which the information about the collision will be added.
		* \remarks Other collider represents either BoundingSphere or PlaneCollider.
		* \return True if collision occured and entry was added to contact manifold, false otherwise
		*/
		bool Collide(const Collider* collider, ContactManifold& manifold) const noexcept override;


		/**
		* \brief Method for collision detection between this collider and Bounding Sphere collider.
		* \param bsphere Pointer to other collider - bounding sphere.
		* \param manifold Reference to contact manifold, to which the information about the collision will be added.
		* \remarks Collision between plane collider and sphere.
		* \return True if collision occured and entry was added to contact manifold, false otherwise
		*/
		bool Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept override;
		
		/*
		* \brief Method for collision detection between this collider and plane collider.
		* \param plane Pointer to other collider - plane colider.
		* \param manifold Reference to contact manifold to which the information about the collision will be added.
		* \return True if collision occured and entry was added to contact manifold, false otherwise
		*/
		bool Collide(const PlaneCollider* plane, ContactManifold& manifold) const noexcept override;


		/**
		* \brief Returns normal vector of the plane collider
		* \return Normal vector of the plane collider
		*/
		const Vec3f& GetPlaneNormal() const noexcept;


		/**
		* \brief Sets normal of the plane collider.
		* \param normal New normal vector of the plane collider.
		*/
		void SetPlaneNormal(const Vec3f& normal) noexcept;


		/**
		* \brief Returns the offset value of the plane collider.
		* \remarks Offset represents additional distance along the normal line between the plane and other collider.
		* \return Normal vector of the plane collider.
		*/
		float GetOffeset() const noexcept;



		/**
		* \brief Sets the offset value of the plane collider.
		* \param offset The offset value of the plane collider.
		* \remarks Offset represents additional distance along the normal line between the plane and other collider.
		*/
		void SetOffset(const float offset) noexcept;

	};
}
#endif