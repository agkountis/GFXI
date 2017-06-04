#include "bounding_sphere.h"
#include "collider_component.h"
#include "entity.h"

using namespace Blade;


BoundingSphere::BoundingSphere(float radius):
	m_Radius{radius}
{

}

bool BoundingSphere::Collide(const Collider* collider, ContactManifold& manifold) const noexcept
{
	return collider->Collide(this, manifold);
}

const float BoundingSphere::GetRadius() const noexcept
{
	return m_Radius;
}

bool BoundingSphere::Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept
{
	Vec3f c1{ bsphere->GetColliderComponent()->GetParent()->GetPosition() };
	Vec3f c2{ GetColliderComponent()->GetParent()->GetPosition() };

	Vec3f midline{ c1 - c2 };

	float size = MathUtils::Lengthf(midline);

	float radSum{ bsphere->GetRadius() + m_Radius };

	if (size <= 0.0f || size >= radSum) 
	{
		return false;
	}

	Vec3f normal{ midline * (1.0f / size) };

	ManifoldEntry entry;

	entry.contactNormal = normal;
	entry.collider1 = bsphere;
	entry.collider2 = this;
	entry.penetration = radSum - size;

	manifold.AddEntry(entry);

	return true;
}

