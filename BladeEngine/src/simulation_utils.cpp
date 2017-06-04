#include "simulation_utils.h"
#include "entity.h"
#include "component.h"
using namespace Blade;



bool SimulationUtils::SphereAndSphereCollision(const BoundingSphere * sphere1, const BoundingSphere * sphere2, ContactManifold & manifold) noexcept
{

	sphere1->GetColliderComponent();
	Vec3f c1{ sphere1->GetColliderComponent()->GetParent()->GetPosition() };
	Vec3f c2{ sphere2->GetColliderComponent()->GetParent()->GetPosition() };

	Vec3f midline{ c1 - c2 };

	float size = MathUtils::Lengthf(midline);

	float radSum{ sphere1->GetRadius() + sphere2->GetRadius()};

	if (size <= 0.0f || size >= radSum)
	{
		return false;
	}

	Vec3f normal{ midline * (1.0f / size) };

	ManifoldEntry entry;

	entry.contactNormal = normal;
	entry.collider1 = sphere1;
	entry.collider2 = sphere2;
	entry.penetration = radSum - size;

	manifold.AddEntry(entry);

	return true;
}

bool Blade::SimulationUtils::SphereAndCylinderCollision(const BoundingSphere * sphere, const BoundingCylinder * cylinder, ContactManifold & manifold) noexcept
{
	//#needtoimplement
	return false;
}

bool Blade::SimulationUtils::SphereAndBoxCollision(const BoundingSphere * sphere, const BoundingBox * box, ContactManifold & manifold) noexcept
{
	//#needtoimplement
	return false;
}

bool Blade::SimulationUtils::SphereAndPlane(const BoundingSphere * sphere, const PlaneCollider * plane, ContactManifold & manifold) noexcept
{
	//#needtoimplement
	return false;
}

bool Blade::SimulationUtils::BoxAndPlane(const BoundingBox * box, const PlaneCollider * plane, ContactManifold & manifold) noexcept
{
	//#needtoimplement
	return false;
}

bool Blade::SimulationUtils::CylinderAndPlane(const BoundingCylinder * cylinder, const PlaneCollider * plane, ContactManifold & manifold) noexcept
{
	//#needtoimplement
	return false;
}
