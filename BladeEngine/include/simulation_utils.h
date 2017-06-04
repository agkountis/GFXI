#include "bounding_box.h"
#include "bounding_cylinder.h"
#include "bounding_sphere.h"
#include "plane_collider.h"


namespace Blade
{
	namespace SimulationUtils
	{
		bool SphereAndSphereCollision(const BoundingSphere* sphere1, const BoundingSphere* sphere2, ContactManifold& manifold) noexcept;
	
		bool SphereAndCylinderCollision(const BoundingSphere* sphere, const BoundingCylinder* cylinder, ContactManifold& manifold) noexcept;

		bool SphereAndBoxCollision(const BoundingSphere* sphere, const BoundingBox* box, ContactManifold& manifold) noexcept;

		bool SphereAndPlane(const BoundingSphere* sphere, const PlaneCollider* plane, ContactManifold& manifold) noexcept;

		bool BoxAndPlane(const BoundingBox* box, const PlaneCollider* plane, ContactManifold& manifold) noexcept;

		bool CylinderAndPlane(const BoundingCylinder* cylinder, const PlaneCollider* plane, ContactManifold& manifold) noexcept;


	}

}