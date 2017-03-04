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
	public:
		RigidBodyComponent(Entity* parent);

		RigidBodyComponent(RigidBodyComponent&) = delete;
		RigidBodyComponent& operator=(RigidBodyComponent&) = delete;
		~RigidBodyComponent();

		/**************** WILL BE REMOVED ONCE COMPONENT DEFINITION STUFF IS SORTED **********/

		/**
		* \brief Performs setup actions after the Component's creation
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

