#include "bounding_sphere.h"
#include "plane_collider.h"


namespace Blade
{
	namespace SimulationUtils
	{
		/*
		\brief Collision detection between spheres.
		*/
		bool SphereAndSphereCollision(const BoundingSphere* sphere1, const BoundingSphere* sphere2, ContactManifold& manifold) noexcept;


		/*
		\brief Collision detection between sphere and plane (half plane).
		*/
		bool SphereAndPlaneCollision(const BoundingSphere* sphere, const PlaneCollider* plane, ContactManifold& manifold) noexcept;
	}
}