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
		* \param Parent enitity pointer - does not take ownership.
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
		void AddForce(Vec3d& f) noexcept;

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
		/**************** WILL BE REMOVED ONCE COMPONENT DEFINITION STUFF IS SORTED **********/

		/**
		* \brief Performs setup actions after the Component's creation.
		*/
		void Setup() noexcept override;

		/**
		* \brief Updates the Component on each frame.
		* \param dt The time elapsed from the previous frame of the Application.
		* \param time The elapsed time since the start of the Application.
		*/
		void Update(float dt, long time = 0) noexcept;

		/**
		* \brief Performs actions before the Component is destroyed.
		*/
		void Teardown() noexcept;

		/******************************************************************************/

	};
}
#endif //BLADE_RIGIDBODY_COMPONENT_H_

