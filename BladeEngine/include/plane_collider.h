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
		/*
		\brief The plane normal
		*/
		Vec3f m_PlaneNormal;

		/*
		\brief The distance of the plane from the origin
		*/
		float m_Offset;
	public:
		explicit PlaneCollider(const Vec3f& planeNormal, const float offset);

		bool Collide(const Collider* collider, ContactManifold& manifold) const noexcept override;

		bool Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept override;
		
		bool Collide(const PlaneCollider* plane, ContactManifold& manifold) const noexcept override;

		const Vec3f& GetPlaneNormal() const noexcept;

		void SetPlaneNormal(const Vec3f& normal) noexcept;

		float GetOffeset() const noexcept;

		void SetOffset(const float offset) noexcept;

	};
}
#endif