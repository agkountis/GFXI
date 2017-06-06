#include "plane_collider.h"
#include "bounding_sphere.h"
#include "simulation_utils.h"
using namespace Blade;

PlaneCollider::PlaneCollider(const Vec3f& planeNormal, const float offset):
	m_PlaneNormal{planeNormal},
	m_Offset{offset}
{
}

bool PlaneCollider::Collide(const Collider* collider, ContactManifold& manifold) const noexcept
{
	return collider->Collide(this, manifold);
}

bool PlaneCollider::Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept
{
	return SimulationUtils::SphereAndPlane(bsphere, this, manifold);
}

bool PlaneCollider::Collide(const PlaneCollider* plane, ContactManifold& manifold) const noexcept
{
	//No collision between planes 
	return false;
}

const Vec3f& PlaneCollider::GetPlaneNormal() const noexcept 
{
	return m_PlaneNormal;
}

void PlaneCollider::SetPlaneNormal(const Vec3f& normal) noexcept
{
	m_PlaneNormal = normal;
}

float PlaneCollider::GetOffeset() const noexcept
{
	return m_Offset;
}

void Blade::PlaneCollider::SetOffset(const float offset) noexcept
{
	m_Offset = offset;
}
