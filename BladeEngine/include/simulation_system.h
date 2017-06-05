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
		
		///*
		//\brief Simulation thread
		//*/
		//std::thread m_Thread;

		///*
		//\brief Mutex that is used by the simulation thread
		//*/
		//std::mutex m_Mutex;

		///*
		//\brief Condition variable where the simulation thread wait until 
		//it's free to start running the simulation
		//*/
		//std::condition_variable m_StartSimulating;

		///*
		//\brief IDK
		//*/
		//std::vector<std::function<void()>> m_IntegrationTasks;

		///*
		//\brief Used to terminate the thread 
		//*/
		//bool m_Terminating{ false };

		///*
		//\brief The simulation system timer
		//\details Since the simulation system runs on its own thread, it 
		//holds a timer to calculate the delta time. 
		//*/
		//Timer m_Timer;

		/*
		\brief Performs integration of the rigid bodies 
		\details This function is provided in order of being able to split the integration process
		of the entire rigid body vector.
		\param startIndex the index of the first rigid body that needs to be integrated
		\param endIndex the index of the last rigid body that we need to integrate
		\param simulationSystem the simulation system
		*/
		//static void IntegrationTask(int startIndex, int endIndex, SimulationSystem* simulationSystem) noexcept;

		/*
		\brief Performs the splitting of the integration process in different tasks
		*/
		//void GenerateIntegrationTasks() noexcept;


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