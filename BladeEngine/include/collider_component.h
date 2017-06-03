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
	class ColliderComponent: public Component
	{

	private:
		bool m_CollisionResponse;
		BoundingVolume* m_pBVolume;
		bool m_ValidFlag;

	protected:
		void BVolume(BoundingVolume* bv) { m_pBVolume = bv; }
		BoundingVolume* BVolume() { return m_pBVolume; }

	public:
		/**
		* \brief Creates collider component without bounding shape.
		* \brief Bounding shape can be created latter with a Create() method.
		* \param Pointer to parent enitity.
		*/
		ColliderComponent(Entity* parent);

		/**
		* \brief Creates collider component with choosen bounding shape.
		* \brief If parent entity has no render component, bounding shape will not be created at construction time.
		* \brief It can be created latter with a Create() method.
		* \param Pointer to parent enitity.
		* \param Bounding volume type to create.
		*/
		ColliderComponent(Entity* parent, BVolumeType type);

		ColliderComponent(ColliderComponent&) = delete;
		ColliderComponent& operator=(ColliderComponent&) = delete;
		~ColliderComponent();


		/**
		* \brief Creates actual component internals(bounding volume) and registers it with SimulationSystem.
		* \param Bounding volume type(Sphere,Box or Cylinder).
		* \return true if successfull.
		*/
		bool CreateBShape(BVolumeType bVolumeType);

		/**
		* \brief Checks if collider is valid - It is if has a bounding volume.
		* \return true if valid.
		*/
		bool isValid();

	};
}
#endif //BLADE_COLLIDER_COMPONENT_H_