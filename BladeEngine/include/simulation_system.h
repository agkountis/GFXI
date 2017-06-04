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
	/*
	\brief The simulation system of the engine
	\details Performs the simulation routine: update, detection, response using threads. 
	*/
	class SimulationSystem : System
	{
	private:
		std::vector<SimulationComponent*> m_RigidBodyComponents;

		std::vector<ColliderComponent*> m_ColliderComponents;

		ContactManifold m_ContactManifold;

		std::thread m_Thread;
		std::mutex m_Mutex;
		std::condition_variable m_StartSimulating;

		std::vector<std::function<void()>> m_IntegrationTasks;

		bool m_Terminating{ false };

		Timer m_Timer;

		static void IntegrationTask(int startIndex, int endIndex, SimulationSystem* simulationSystem) noexcept;

		void GenerateIntegrationTasks() noexcept;

		void CollisionDetection() noexcept;

		void CollisionResponse() const noexcept;

	public:

		static float frequency;

		static float elasticity;

		static float friction;

		static float dt;

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

		const Timer& GetTimer() const noexcept;

		void Start() noexcept;
	};
}
#endif //BLADE_SIMULATION_SYSTEM_H_