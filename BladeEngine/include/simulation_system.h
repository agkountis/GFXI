#ifndef BLADE_SIMULATION_SYSTEM_H_
#define BLADE_SIMULATION_SYSTEM_H_
#include <vector>
#include "system.h"
#include "collider_component.h"
#include "simulation_component.h"
#include "timer.h"
#include <thread>
#include <mutex>
#include "contact_manifold.h"

namespace Blade
{
	/**
	\brief The simulation system of the engine
	\details Performs the simulation routine: update, detection, response using threads. 
	*/
	class SimulationSystem : System
	{
	private:
		/*
		\brief Stores the simulation components registered to the system. 
		*/
		std::vector<SimulationComponent*> m_SimulationComponents;

		/*
		\brief Stores the collider components registered to the system
		*/
		std::vector<ColliderComponent*> m_ColliderComponents;

		/*
		\brief Contact manifold of the simulation
		\details One manifold is sufficient to cover the entire simulation 
		*/
		ContactManifold m_ContactManifold;

		/*
		\brief Perform the integration of simulation components
		*/
		void UpdateSimComponents() noexcept;

		/*
		\brief Collision detection routine of the simulation
		\details Check exhaustive collision between every active collision component. 
		It populates the manifold.
		*/
		void GenerateContacts() noexcept;

		/*
		\brief Collision response routine of the simulation
		\details Calculate the new position, velocity and orientation of two colliding objects.
		The collision response process is not iterative. 
		*/
		void CollisionResponse() const noexcept;

		/*
		\brief Prepare the contact before the response. Stores pointer used by the other subroutines.
		*/
		void PreResponse(Entity* &e1, ManifoldEntry &entry, Entity* &e2,
			SimulationComponent* &simCo1, SimulationComponent* &simCo2) const noexcept;

		/*
		\brief Integrate the current simulation component position.
		*/
		void Integrate(SimulationComponent * simulationComponent) noexcept;

		/*
		\brief Changes the position of the entities colliding.
		\details If one entity does not hold a rigid body, the position won't change. 
		*/
		void ApplyPositionChanges(const Vec3f& contactNormal, const float penetration,
			SimulationComponent* simcom1, Entity* e1, SimulationComponent* simcom2, Entity* e2) const noexcept;

		/*
		\brief Changes the velocity of the entities colliding. This method is used inside the collision response pass.
		*/
		void ApplyVelocityChanges(SimulationComponent* simCom1, SimulationComponent* simCom2, ManifoldEntry &entry) const noexcept;

		/*
		\brief Set the velocity of the two simulation components that are colliding.
		*/
		void SetVelocity(SimulationComponent* sc1, SimulationComponent* sc2, float newSeparatingVelocity, float separatingVelocity, Vec3f& contactNormal) const noexcept;

	public:
		/*
		\brief The frequency of the simulation thread
		*/
		static float frequency;

		/*
		\brief The elasticity factor of the entire simulation.
		\details The elasticity can be changed at runtime.
		*/
		static float elasticity;

		/*
		\brief The friction factor of the simulation.
		\details The friction scalar can be changed at runtime.
		*/
		static float friction;

		/*
		\brief Simulation system delta time
		*/
		static float dt;

		/*
		\brief Simulation system delta time scale 
		\details Can be used to tweak the delta time of the simulation.
		*/
		static float dtScale;

		/*
		\brief Time in second of the application
		*/
		float timeSec;

		SimulationSystem() = default;

		SimulationSystem& operator=(SimulationSystem&) = delete;

		SimulationSystem(SimulationSystem&) = delete;

		~SimulationSystem();

		/*
		\brief Initialize the simulation system.
		*/
		bool Initialize() noexcept override;

		/*
		\brief Perform the simulation loop: update the simulation, calculate the contacts 
		and store them inside the manifold and then resolve the contacts.
		*/
		void Process(float deltaTime) noexcept override;

		/*
		\brief Register a simulation component to the system
		\param simComp the new component that needs to be registered to the system.
		*/
		void RegisterComponent(SimulationComponent* simComp) noexcept;

		/*
		\brief Register a collider component to the system
		\param colComp the new component that needs to be registered to the system.
		*/
		void RegisterComponent(ColliderComponent* colComp) noexcept;

		/*
		\brief Unregister a simulation component to the system, that component won't be update 
		anymore.
		\param simComp the pointer to the SimulationComponent that we need to remove.
		*/
		void UnregisterComponent(SimulationComponent* simComp) noexcept;

		/*
		\brief Unregister a collider component to the system, that component won't be taken 
		in consideration for further collision detection and therefore response.
		\param simComp the pointer to the ColliderComponent that we need to remove.
		*/
		void UnregisterComponent(ColliderComponent* colComp) noexcept;

		/*
		\brief Returns a vector of the simulation components that the system holds.
		*/
		const std::vector<SimulationComponent*>& GetSimulationComponents() const noexcept;
	};
}
#endif //BLADE_SIMULATION_SYSTEM_H_