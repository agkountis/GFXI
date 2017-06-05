#include "bounding_sphere.h"
#include "plane_collider.h"


namespace Blade
{
	namespace SimulationUtils
	{
		bool SphereAndSphereCollision(const BoundingSphere* sphere1, const BoundingSphere* sphere2, ContactManifold& manifold) noexcept;

		bool SphereAndPlane(const BoundingSphere* sphere, const PlaneCollider* plane, ContactManifold& manifold) noexcept;
	}
}