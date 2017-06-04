#include "plane_collider.h"

using namespace Blade;

PlaneCollider::PlaneCollider(const Vec3f& planeNormal, const float offset):
	m_PlaneNormal{planeNormal},
	m_Offset{offset}
{

}

bool PlaneCollider::Collide(const Collider* collider, ContactManifold& manifold) const noexcept
{
	return false;
}

bool PlaneCollider::Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept
{
	//#needtoimplement
	/*
	
	// Cache the sphere position
	XMFLOAT3 position = sphere.GetAxis(3);
	//Find the distance from the plane
	XMVECTOR v_plane_direction = XMLoadFloat3(&plane._direction);
	XMVECTOR v_sphere_axis = XMLoadFloat3(&sphere.GetAxis(3));
	XMVECTOR aux = XMVector3Dot(v_plane_direction, v_sphere_axis);
	XMFLOAT3 aux2;
	XMStoreFloat3(&aux2, aux);

	F32 centreDistance{ aux2.x - plane._offset };

	//Check if we're within the radius
	if (centreDistance*centreDistance > sphere._radius*sphere._radius)
	{
		return 0;
	}

	//Check which side of the plane we are on
	XMFLOAT3 normal = plane._direction;
	XMVECTOR v_normal = XMLoadFloat3(&normal);
	F32 penetration = -centreDistance;
	if (centreDistance < 0.0f)
	{
		v_normal *= -1;
		XMStoreFloat3(&normal, v_normal);
		penetration = -penetration;
	}
	penetration += sphere._radius;

	//Create the contact - it has normal in the plane direction
	Contact * contact = data->contacts;
	contact->contactNormal = normal;
	contact->penetration = penetration;
	contact->SetBodyData(sphere._body, nullptr, data->friction, data->restitution);
	//Calculate the contact point
	XMVECTOR v_position = XMLoadFloat3(&position);
	XMVECTOR v_contactPoint;
	v_contactPoint = v_position - v_plane_direction *centreDistance;
	XMStoreFloat3(&contact->contactPoint, v_contactPoint);

	data->AddContact(1);
	*/
	return true;
}
