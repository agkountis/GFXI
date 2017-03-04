#ifndef BLADE_COLLIDER_COMPONENT_H_
#define BLADE_COLLIDER_COMPONENT_H_

#include "component.h"
#include "bounding_volume.h"
enum class BVolumeType
{
	Sphere, 
	Box, 
	Cylinder
};
namespace Blade
{
	class Entity;
	class ColliderComponent // will inherit from component, but after we sort out the behaviours and stuff
	{

	private:
		bool m_CollisionResponse;
		BoundingVolume* m_pBVolume;


	public:
		ColliderComponent(Entity* parent, BVolumeType bVolumeType);
		ColliderComponent(ColliderComponent&) = delete;
		ColliderComponent& operator=(ColliderComponent&) = delete;
		~ColliderComponent();
	};
}
#endif //BLADE_COLLIDER_COMPONENT_H_