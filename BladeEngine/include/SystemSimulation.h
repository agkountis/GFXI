#ifndef BLADE_SIMULATION_SYSTEM_H_
#define BLADE_SIMULATION_SYSTEM_H_

#include <vector>

#include "System.h"
#include "component.h" // just temporary!
#include "collider_component.h"
#include "rigid_body_component.h"



namespace Blade
{
	class SystemSimulation : System
	{
	private:
		 // TO DO: Add data members
		std::vector<RigidBodyComponent*> m_RigidBodyList;
		std::vector<ColliderComponent*> m_ColliderList;

	public:
		SystemSimulation() = default;
		SystemSimulation& operator=(SystemSimulation&) = delete;
		SystemSimulation(SystemSimulation&) = delete;
		~SystemSimulation();


		/**
		* \brief Performs system initialization.
		* \return TRUE if initialization is successfull, FALSE otherwise.
		*/
		bool Initialize() noexcept override;

		/**
		* \brief Updates physics simulation.
		* \param deltaTime The time elapsed from the previous frame of the application.
		*/
		void Process(float deltaTime) noexcept override;

		//*** SYSTEM SIMULATION SPECIFIC METHODS

		/**
		* \brief Registers Rigid Body Component with the Simulation System.
		* \param rbc Pointer to the component - DOES NOT TAKE OWNERSHIP
		*/
		void RegisterComponent(RigidBodyComponent* rbc) noexcept;

		/**
		* \brief Registers Collider Component with the Simulation System.
		* \param rbc Pointer to the component - DOES NOT TAKE OWNERSHIP
		*/
		void RegisterComponent(ColliderComponent* col) noexcept ;

		/**
		* \brief Unregisters a given Component with the Simulation System(if it is registered).
		* \param rbc Pointer to the component
		*/
		void UnregisterComponent(Component* c) noexcept;
	};
}
#endif //BLADE_SIMULATION_SYSTEM_H_