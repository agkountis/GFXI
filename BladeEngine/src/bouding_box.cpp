#include "bounding_box.h"
using namespace Blade;

BoundingBox::BoundingBox(const Vec3f& size):m_Size {size}
{

}


bool BoundingBox::Collide(const Collider* collider, ContactManifold& manifold) const noexcept
{
	//#needtoimplement
	return false;
}


bool BoundingBox::Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept
{
	//#needtoimplement
	return true;
}