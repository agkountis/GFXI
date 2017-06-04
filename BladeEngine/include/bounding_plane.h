#ifndef BLADE_BOUNDING_PLANE_H_
#define BLADE_BOUNDING_PLANE_H_
#include "collider.h"
#include "contact_manifold.h"

namespace Blade
{
	/**
	* \brief Bounding Plane class is a collider
	*/
	class BoundingPlane : public Collider
	{
	private:
		/*
		\brief The plane normal
		*/
		Vec3f m_PlaneNormal;

		/*
		\brief The distance of the plane from the origin
		*/
		float m_Offset;
	public:
		explicit BoundingPlane(const Vec3f& planeNormal, const float offset);

		bool Collide(const Collider* collider, ContactManifold& manifold) const noexcept override;

		bool Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept override;
	};
}
#endif