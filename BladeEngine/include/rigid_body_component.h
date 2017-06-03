#ifndef BLADE_RIGIDBODY_COMPONENT_H_
#define BLADE_RIGIDBODY_COMPONENT_H_

#include "component.h"
namespace Blade
{
	class Entity;
	class RigidBodyComponent : public Component // will inherit from component, but after we sort out the behaviours and stuff
	{

	private:
		//TO DO: Add all relevant members
		Vec3d m_Velocity;
		float m_Mass;
	public:
		/**
		* \brief Constructs RigidBodyComponent with mass "mass"
		* \param Parent entity pointer - does not take ownership.
		* \param Mass of the body - Kilograms assumed
		*/
		RigidBodyComponent(Entity* parent, float mass);


		/**
		* \brief Constructs RigidBodyComponent with mass "mass"
		* \param Parent enitity pointer - does not take ownership.
		* \param Density of the body - Kilograms/meters^3 assumed.
		* \param Volume of the body -meters^3 assumed.
		*/
		RigidBodyComponent(Entity* parent, float density, float volume);

		RigidBodyComponent(RigidBodyComponent&) = delete;
		RigidBodyComponent& operator=(RigidBodyComponent&) = delete;
		~RigidBodyComponent();

		/**
		* \brief Adds force to the rigid body.
		* \param Force vector to add.
		*/
		void AddForce(Vec3d& force) noexcept;

		/**
		* \brief Adds force to the rigid body.
		* \return Body velocity vector.
		*/
		Vec3d GetVelocity() const noexcept;

		/**
		* \brief Gets mass(kgs assumed).
		* \return Mass in kilograms.
		*/
		float GetMass() const noexcept;

	};
}
#endif //BLADE_RIGIDBODY_COMPONENT_H_

