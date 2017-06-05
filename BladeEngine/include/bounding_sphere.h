#ifndef BLADE_BOUNDING_SPHERE
#define BLADE_BOUNDING_SPHERE
#include "collider.h"
#include "contact_manifold.h"

namespace Blade
{
	/*
	\brief BoundingSphere class of the engine is a Collider
	*/
	class BoundingSphere : public Collider
	{
	private:
		/*
		\brief The radius of the bounding sphere collider
		*/
		float m_Radius;

	public:
		explicit BoundingSphere(float radius);

		bool Collide(const Collider* collider, ContactManifold& manifold) const noexcept override;

		bool Collide(const BoundingSphere* bsphere, ContactManifold& manifold) const noexcept override;

		const float GetRadius() const noexcept;
	};
}
#endif