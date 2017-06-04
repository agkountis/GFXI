#ifndef BLADE_BOUNDING_CYLINDER_H_
#define BLADE_BOUNDING_CYLINDER_H_
#include "collider.h"
#include "contact_manifold.h"

namespace Blade
{
	/**
	* \brief Bounding Cylinder class is a collider
	*/
	class BoundingCylinder : public Collider
	{
	private:
		/*
		\brief Height of the cylinder
		*/
		float m_Height;

		/*
		\brief Radius of the cylinder
		*/
		float m_Radius;
	public:
		explicit BoundingCylinder(float height, float radius);

		bool Collide(const Collider* collider, ContactManifold& manifold) const noexcept override;

		bool Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept override;
	};
}
#endif