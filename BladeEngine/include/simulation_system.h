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
		//////////////////////////////////////////////////////////////////////////

		/*
		\brief Perform the integration of the rigid bodies
		*/
		void UpdateObjects() noexcept;
		/*
		\brief Collision detection routine of the simulation
		\details Check exhaustive collision between every active collision component. 
		It populates the manifold.
		*/
		void CollisionDetection() noexcept;

		/*
		\brief Collision response routine of the simulation
		\details Calculate the new position, velocity and orientation of two colliding objects.
		The collision response process is not iterative. 
		*/
		void CollisionResponse() const noexcept;

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

		float timeSec;

		SimulationSystem() = default;

		SimulationSystem& operator=(SimulationSystem&) = delete;

		SimulationSystem(SimulationSystem&) = delete;

		~SimulationSystem();


		bool Initialize() noexcept override;

		void Process(float deltaTime) noexcept override;

		void RegisterComponent(SimulationComponent* rbc) noexcept;

		void RegisterComponent(ColliderComponent* col) noexcept;

		void UnregisterComponent(SimulationComponent* c) const noexcept;

		void UnregisterComponent(ColliderComponent* c) noexcept;

		const std::vector<SimulationComponent*>& GetRigidBodyComponents() const noexcept;

	};
}
#endif //BLADE_SIMULATION_SYSTEM_H_