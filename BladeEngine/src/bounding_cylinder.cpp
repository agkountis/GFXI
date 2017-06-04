#include "bounding_cylinder.h"

using namespace Blade;

BoundingCylinder::BoundingCylinder(float height, float radius):
	m_Height{height},
	m_Radius{radius}
{
}

bool BoundingCylinder::Collide(const Collider* collider, ContactManifold& manifold) const noexcept
{
	//#needtoimplement
	return false;
}

bool BoundingCylinder::Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept
{
	//#needtoimplement
	return true;
}


