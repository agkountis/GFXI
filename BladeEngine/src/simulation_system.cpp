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

	void SimulationSystem::Integrate(SimulationComponent * simulationComponent) noexcept
	{
		Entity* parent{ simulationComponent->GetParent() };
		if (simulationComponent->IsActive())
		{

			float mass{ simulationComponent->GetMass() };

			Vec3f gravityForce{ 0.0f, -9.81f, 0.0f };

			simulationComponent->AddForce(gravityForce);

			Vec3f position{ parent->GetLocalPosition() };
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
		SimulationComponent* simcom1, Entity* e1, SimulationComponent* simcom2, Entity* e2) const noexcept
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

			e1->SetPosition(e1->GetLocalPosition() + move1);

			if (e2)
			{
				e2->SetPosition(e2->GetLocalPosition() + move2);
			}
	}

	void SimulationSystem::SetVelocity(SimulationComponent* sc1, SimulationComponent* sc2,
		float newSeparatingVelocity, float separatingVelocity, Vec3f& contactNormal) const noexcept
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

			if(simCo1)
			{
				ApplyVelocityChanges(simCo1, simCo2, entry);
				if (entry.penetration > 0.0f)
				{
					ApplyPositionChanges(entry.contactNormal, entry.penetration, simCo1, e1, simCo2, e2);
				}
			}
		}
	}

	void SimulationSystem::PreResponse(Entity *& e1, ManifoldEntry & entry, Entity *& e2, 
		SimulationComponent *& simCo1, SimulationComponent *& simCo2) const noexcept
	{
		e1 = entry.collider1->GetColliderComponent()->GetParent();
		if (entry.collider2)
		{
			e2 = entry.collider2->GetColliderComponent()->GetParent();
		}
		if(e1->GetComponent("co_sim"))
		{
		simCo1 = static_cast<SimulationComponent*>(e1->GetComponent("co_sim"));
		}
		if (e2)
		{
			if(e1->GetComponent("co_sim"))
			{
			simCo2 = static_cast<SimulationComponent*>(e2->GetComponent("co_sim"));
			}
		}
	}

	void SimulationSystem::ApplyVelocityChanges(SimulationComponent* simCom1, SimulationComponent* simCom2,
		ManifoldEntry &entry) const noexcept
	{
			Vec3f relativeVelocity{ simCom1->GetVelocity() };
			if (simCom2)
			{
				relativeVelocity -= simCom2->GetVelocity();
			}
			float separatingVelocity{ Dotf(relativeVelocity, entry.contactNormal) };
			if (separatingVelocity < 0.0f)
			{
				float newSeparatingVelocity{ -separatingVelocity * elasticity };
				Vec3f accCausedVelocity{ simCom1->GetAcceleration() };
				if (simCom2)
				{
					accCausedVelocity -= simCom2->GetAcceleration();
				}
				float accCausedSepVelocity{ Dotf(accCausedVelocity, entry.contactNormal) * dt };
				if (accCausedSepVelocity < 0.0f)
				{
					newSeparatingVelocity += elasticity * accCausedSepVelocity;
					if (newSeparatingVelocity < 0.0f)
					{
						newSeparatingVelocity = 0.0f;
					}

					SetVelocity(simCom1, simCom2, newSeparatingVelocity, separatingVelocity, entry.contactNormal);
					return;
				}
				else
				{
					SetVelocity(simCom1, simCom2, newSeparatingVelocity, separatingVelocity, entry.contactNormal);

				}
			}
	}

	SimulationSystem::~SimulationSystem()
	{
		
	}

	bool SimulationSystem::Initialize() noexcept
	{
		return true;
	}

	void SimulationSystem::Process(float deltaTime/*=.0f*/, long time/*=0*/) noexcept
	{
		dt = deltaTime;
		timeSec = static_cast<float>(G_Application.GetSec());
		
		//Integrate all the component stored in the m_SimulationComponets
		UpdateSimComponents();
		//Populate the manifold
		CollisionDetection();
		//Resolve the contact stored in the manifold = change velocity & change position.
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

	void SimulationSystem::UnregisterComponent(SimulationComponent* c)  noexcept
	{
		auto it{ m_SimulationComponents.begin() };

		while (it != m_SimulationComponents.end())
		{
			auto entry{ *it };
			if (entry->GetId() == c->GetId())
			{
				it = m_SimulationComponents.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void SimulationSystem::UnregisterComponent(ColliderComponent* c) noexcept
	{
		auto it{ m_ColliderComponents.begin() };

		while (it != m_ColliderComponents.end())
		{
			auto entry{ *it };
			if (entry->GetId() == c->GetId())
			{
				it = m_ColliderComponents.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	const std::vector<SimulationComponent*>& SimulationSystem::GetSimulationComponents() const noexcept
	{
		return m_SimulationComponents;
	}

}
