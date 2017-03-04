#include "collider_component.h"
#include "bounding_sphere.h"
#include "bounding_box.h"
#include "bounding_cylinder.h"

namespace Blade
{
	ColliderComponent::ColliderComponent(Entity* parent, BVolumeType bVolumeType) :
		m_CollisionResponse{ true },
		m_pBVolume{nullptr}
	{
		//TO DO: Create appropriate bounding shape based on caller's preference 
		//if(bVolumeType == BVolumeType::Sphere) m_pBVolume = new BoundingSphere(parent->)
	}


	ColliderComponent::~ColliderComponent()
	{
		
	}
}