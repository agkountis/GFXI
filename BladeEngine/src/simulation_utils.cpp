#include "simulation_utils.h"
#include "entity.h"
#include "component.h"
#include "bounding_sphere.h"
using namespace Blade;



bool SimulationUtils::SphereAndSphereCollision(const BoundingSphere * sphere1, const BoundingSphere * sphere2, ContactManifold & manifold) noexcept
{
/*
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
	*/
	return true;
}


bool Blade::SimulationUtils::SphereAndPlane(const BoundingSphere * sphere, const PlaneCollider * plane, ContactManifold & manifold) noexcept
{
	//#needtoimplement
	return false;
}

