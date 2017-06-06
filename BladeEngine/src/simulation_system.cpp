#include <vector>
#include "simulation_system.h"
#include "entity.h"
#include "threading_utils.h"
#include <iostream>
#include "bounding_sphere.h"
#include "engine_context.h"
#include "application.h"

#undef max
#undef min

namespace Blade
{
	using namespace MathUtils;

	float SimulationSystem::frequency = 2000.0f;
	float SimulationSystem::elasticity = 0.5f;
	float SimulationSystem::friction = 0.2f;
	float SimulationSystem::dt = 0.0f;
	float SimulationSystem::dtScale = 1.0f;


	void SimulationSystem::UpdateSimComponents() noexcept
{
		for (auto simulationComponent : m_SimulationComponents)
		{
			Integrate(simulationComponent);
		}
	}

	void SimulationSystem::Integrate(SimulationComponent * simulationComponent)
	{
		Entity* parent{ simulationComponent->GetParent() };
		if (simulationComponent->IsActive())
		{

			float mass{ simulationComponent->GetMass() };

			Vec3f gravityForce{ 0.0f, -9.81f, 0.0f };

			simulationComponent->AddForce(gravityForce);

			Vec3f position{ parent->GetPosition() };
			simulationComponent->SetPreviousPosition(position);

			Vec3f velocity{ simulationComponent->GetVelocity() };
			simulationComponent->SetPreviousVelocity(velocity);

			Vec3f force{ simulationComponent->GetForce() * mass };
			simulationComponent->SetPreviousForce(force);

			simulationComponent->SetAcceleration(force / mass);

			RungeKutta4Integrator::Integrate(position, velocity, force, mass, timeSec, dt);

			parent->SetPosition(position);

			simulationComponent->SetVelocity(velocity);

			simulationComponent->ResetForce();
		}
	}

	void SimulationSystem::ApplyPositionChanges(const Vec3f& contactNormal, const float penetration,
		SimulationComponent* simcom1, Entity* e1, SimulationComponent* simcom2, Entity* e2) const
	{
		float totalInverseMass{ simcom1->GetInverseMass() };

		if (simcom2)
		{
			totalInverseMass += simcom2->GetInverseMass();
		}

		if (totalInverseMass <= 0)
		{
			return;
		}

		Vec3f movePerInverseMass{ contactNormal * (penetration / totalInverseMass) };

		Vec3f move1{ movePerInverseMass * simcom1->GetInverseMass() };
		Vec3f move2;

		if (simcom2)
		{
			move2 = movePerInverseMass * -simcom2->GetInverseMass();
		}

		e1->SetPosition(e1->GetPosition() + move1);

		if (e2)
		{
			e2->SetPosition(e2->GetPosition() + move2);
		}
	}

	void SimulationSystem::SetVelocity(SimulationComponent* sc1, SimulationComponent* sc2, float newSeparatingVelocity, float separatingVelocity, Vec3f& contactNormal) const
	{
		float deltaVelocity{ newSeparatingVelocity - separatingVelocity };
		float totalInverseMass{ sc1->GetInverseMass() };
		if (sc2)
		{
			totalInverseMass += sc2->GetInverseMass();
		}
		if (totalInverseMass <= 0)
		{
			return;
		}
		float impulse{ deltaVelocity / totalInverseMass };
		Vec3f impulsePerInverseMass{ contactNormal * impulse };
		sc1->SetVelocity(sc1->GetVelocity() + impulsePerInverseMass * sc1->GetInverseMass());
		sc1->SetVelocity(sc1->GetVelocity() - sc1->GetVelocity() * sc1->GetMass() * friction * dt);
		if (sc2)
		{
			sc2->SetVelocity(sc2->GetVelocity() + impulsePerInverseMass * -sc2->GetInverseMass());
			sc2->SetVelocity(sc2->GetVelocity() - sc2->GetVelocity() * sc2->GetMass() * friction * dt);
		}
	}


	void SimulationSystem::CollisionDetection() noexcept
	{
		m_ContactManifold.Clear();

		int offs = 1;
		for (size_t i = 0; i < m_ColliderComponents.size(); ++i)
		{
			auto c1 = m_ColliderComponents[i];

			if (c1->IsActive())
			{
				auto collider = c1->GetCollider();
				for (size_t j = offs; j < m_ColliderComponents.size(); ++j)
				{
					auto c2 = m_ColliderComponents[j];
					if (!c2->IsActive())
					{
						continue;
					}

					collider->Collide(c2->GetCollider(), m_ContactManifold);
				}
			}
			++offs;
		}
	}

	void SimulationSystem::CollisionResponse() const noexcept
	{
		for (size_t i = 0; i < m_ContactManifold.Size(); ++i)
		{
			auto entry = m_ContactManifold[i];

			Entity* e1{ nullptr };
			Entity* e2{ nullptr };
			SimulationComponent* simCo1{ nullptr };
			SimulationComponent* simCo2{ nullptr };

			PreResponse(e1, entry, e2, simCo1, simCo2);

		
			ApplyVelocityChanges(simCo1, simCo2, entry);
			if (entry.penetration > 0.0f)
			{
				ApplyPositionChanges(entry.contactNormal, entry.penetration, simCo1, e1, simCo2, e2);
			}
		}
	}

	void SimulationSystem::PreResponse(Entity *& e1, ManifoldEntry & entry, Entity *& e2, SimulationComponent *& simCo1, SimulationComponent *& simCo2) const
	{
		e1 = entry.collider1->GetColliderComponent()->GetParent();

		if (entry.collider2)
		{
			e2 = entry.collider2->GetColliderComponent()->GetParent();
		}

		simCo1 = static_cast<SimulationComponent*>(e1->GetComponent("co_sim"));

		if (e2)
		{
			simCo2 = static_cast<SimulationComponent*>(e2->GetComponent("co_sim"));
		}
	}

	void SimulationSystem::ApplyVelocityChanges(SimulationComponent * rb1, SimulationComponent * rb2, ManifoldEntry & entry) const
	{
		Vec3f relativeVelocity{ rb1->GetVelocity() };
		if (rb2)
		{
			relativeVelocity -= rb2->GetVelocity();
		}
		float separatingVelocity{ Dotf(relativeVelocity, entry.contactNormal) };
		if (separatingVelocity < 0.0f)
		{
			float newSeparatingVelocity{ -separatingVelocity * elasticity };
			Vec3f accCausedVelocity{ rb1->GetAcceleration() };
			if (rb2)
			{
				accCausedVelocity -= rb2->GetAcceleration();
			}
			float accCausedSepVelocity{ Dotf(accCausedVelocity, entry.contactNormal) * dt };
			if (accCausedSepVelocity < 0.0f)
			{
				newSeparatingVelocity += elasticity * accCausedSepVelocity;
				if (newSeparatingVelocity < 0.0f)
				{
					newSeparatingVelocity = 0.0f;
				}

				SetVelocity(rb1, rb2, newSeparatingVelocity, separatingVelocity, entry.contactNormal);
				return;
			}
			else
			{
				SetVelocity(rb1, rb2, newSeparatingVelocity, separatingVelocity,  entry.contactNormal);

			}
		}
	}

	SimulationSystem::~SimulationSystem()
	{
		/*m_Terminating = true;

		m_IntegrationTasks.clear();

		if (m_Thread.joinable())
		{
			m_Thread.join();
		}*/
	}

	bool SimulationSystem::Initialize() noexcept
	{
		return true;
	}

	void SimulationSystem::Process(float deltaTime) noexcept
	{
		dt = deltaTime;
		timeSec = static_cast<float>(G_Application.GetSec());

		UpdateSimComponents();

		CollisionDetection();

		CollisionResponse();
	}

	void SimulationSystem::RegisterComponent(SimulationComponent* rbc) noexcept
	{
		m_SimulationComponents.push_back(rbc);
	}

	void SimulationSystem::RegisterComponent(ColliderComponent* col) noexcept
	{
		m_ColliderComponents.push_back(col);
	}

	void SimulationSystem::UnregisterComponent(SimulationComponent* c) const noexcept
	{
		/*std::remove_if(m_SimulationComponents.begin(),
			m_SimulationComponents.end(),
			[c](SimulationComponent* element) {
			return c->GetId() == element->GetId();
		});*/
	}

	void SimulationSystem::UnregisterComponent(ColliderComponent* c) noexcept
	{
		std::remove_if(m_ColliderComponents.begin(),
			m_ColliderComponents.end(),
			[c](ColliderComponent* element) {
			return c->GetId() == element->GetId();
		});
	}

	const std::vector<SimulationComponent*>& SimulationSystem::GetRigidBodyComponents() const noexcept
	{
		return m_SimulationComponents;
	}

}
