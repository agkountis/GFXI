#ifndef BLADE_BOUNDING_BOX_H_
#define BLADE_BOUNDING_BOX_H_

#include "collider.h"
#include "math_utils.h"
#include "contact_manifold.h"

namespace Blade
{
	/**
	* \brief Bounding Box class is a Collider
	*/
	class BoundingBox : public Collider
	{

	private:
		Vec3f m_Size;
	public:

		explicit BoundingBox(const Vec3f& size);

		bool Collide(const Collider* collider, ContactManifold& manifold) const noexcept override;

		bool Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept override;
	};


}

#endif