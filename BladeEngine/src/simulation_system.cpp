#include <vector>
#include "simulation_system.h"
#include "entity.h"
#include "threading_utils.h"
#include <iostream>
#include "bounding_sphere.h"
#include "engine_context.h"
#include "application.h"

#include "trace.h"	//#needtoremove

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


	void SimulationSystem::UpdateObjects() noexcept
	{
		for (auto simulationComponent : m_SimulationComponents)
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

				float angleX = velocity.z * simulationComponent->GetInverseMass() * friction * dtScale;
				float angleZ = velocity.x * simulationComponent->GetInverseMass() * friction * dtScale;

				if (G_Application.IsPaused())
				{
					angleX = angleZ = 0.0f;
					BLADE_TRACE("paused sim");

				}
				Quatf q;
				Quatf xrot = Rotate(q, ToRadians(angleX), Vec3f{ 1.0f, 0.0f, 0.0f });
				Quatf yrot = Rotate(q, ToRadians(-angleZ), Vec3f{ 0.0f, 0.0f, 1.0f });

				q = xrot * yrot;

				q = Normalize(q);

				parent->SetOrientation(parent->GetOrientation() * q);

				simulationComponent->ResetForce();
			}
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

				// Plane collision detection -----------------------------------------
				Vec3f planeDir{ 0.0f, 1.0f, 0.0f };
				float planeOffset{ 0.0f };

				float sphereDistance{ Dotf(planeDir, c1->GetParent()->GetPosition()) - 0.5f - planeOffset };

				if (sphereDistance <= 0.0f)
				{
					ManifoldEntry entry;
					entry.collider1 = collider;
					entry.collider2 = nullptr;
					entry.contactNormal = planeDir;
					entry.penetration = -sphereDistance;

					m_ContactManifold.AddEntry(entry);
				}

				// --------------------------------------------------------------------------
				// Cylinder collision detection------------------------------------------------
				float radius{ 20.0f };

				Vec3f p{ c1->GetParent()->GetPosition() };

				float len = Lengthf(p.xz);
				if (len > radius - 0.5f)
				{
					ManifoldEntry entry;
					entry.collider1 = collider;
					entry.collider2 = nullptr;
					entry.contactNormal = Normalize(-Vec3f{ p.x, 0.0, p.z });
					entry.penetration = Lengthf(p.xz) - radius;

					m_ContactManifold.AddEntry(entry);
				}
				//-----------------------------------------------------------------------------
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

			e1 = entry.collider1->GetColliderComponent()->GetParent();

			if (entry.collider2)
			{
				e2 = entry.collider2->GetColliderComponent()->GetParent();
			}

			SimulationComponent* rb1{ nullptr };
			SimulationComponent* rb2{ nullptr };

			rb1 = static_cast<SimulationComponent*>(e1->GetComponent("co_sim"));

			if (e2)
			{
				rb2 = static_cast<SimulationComponent*>(e2->GetComponent("co_sim"));
			}

			Vec3f relativeVelocity{ rb1->GetVelocity() };

			if (rb2)
			{
				relativeVelocity -= rb2->GetVelocity();
			}

			float separatingVelocity{ Dotf(relativeVelocity, entry.contactNormal) };

			// Resolve velocities
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

					float deltaVelocity{ newSeparatingVelocity - separatingVelocity };

					float totalInverseMass{ rb1->GetInverseMass() };

					if (rb2)
					{
						totalInverseMass += rb2->GetInverseMass();
					}

					if (totalInverseMass <= 0)
					{
						continue;
					}

					float impulse{ deltaVelocity / totalInverseMass };

					Vec3f impulsePerInverseMass{ entry.contactNormal * impulse };

					rb1->SetVelocity(rb1->GetVelocity() + impulsePerInverseMass * rb1->GetInverseMass());

					rb1->SetVelocity(rb1->GetVelocity() - rb1->GetVelocity() * rb1->GetMass() * friction * dt);
					if (rb2)
					{
						rb2->SetVelocity(rb2->GetVelocity() + impulsePerInverseMass * -rb2->GetInverseMass());
						rb2->SetVelocity(rb2->GetVelocity() - rb2->GetVelocity() * rb2->GetMass() * friction * dt);
					}
				}
				else
				{
					float deltaVelocity{ newSeparatingVelocity - separatingVelocity };

					float totalInverseMass{ rb1->GetInverseMass() };

					if (rb2)
					{
						totalInverseMass += rb2->GetInverseMass();
					}

					if (totalInverseMass <= 0)
					{
						continue;
					}

					float impulse{ deltaVelocity / totalInverseMass };

					Vec3f impulsePerInverseMass{ entry.contactNormal * impulse };

					rb1->SetVelocity(rb1->GetVelocity() + impulsePerInverseMass * rb1->GetInverseMass());
					rb1->SetVelocity(rb1->GetVelocity() - rb1->GetVelocity() * rb1->GetMass() * friction * dt);
					if (rb2)
					{
						rb2->SetVelocity(rb2->GetVelocity() + impulsePerInverseMass * -rb2->GetInverseMass());
						rb2->SetVelocity(rb2->GetVelocity() - rb2->GetVelocity() * rb2->GetMass() * friction * dt);
					}

					float angleX = rb1->GetVelocity().z * rb1->GetInverseMass();
					float angleZ = rb1->GetVelocity().x * rb1->GetInverseMass();

					Quatf q = e1->GetOrientation();
					q = Rotate(q, ToRadians(angleZ), Vec3f{ 0.0f, 0.0f, 1.0f });
					q = Rotate(q, ToRadians(angleX), Vec3f{ 1.0f, 0.0f, 0.0f });

					q = Normalize(q);

					e1->SetOrientation(q);
				}
			}

			// Resolve penetration.
			if (entry.penetration > 0.0f)
			{
				float totalInverseMass{ rb1->GetInverseMass() };

				if (rb2)
				{
					totalInverseMass += rb2->GetInverseMass();
				}

				if (totalInverseMass <= 0)
				{
					continue;
				}

				Vec3f movePerInverseMass{ entry.contactNormal * (entry.penetration / totalInverseMass) };

				Vec3f move1{ movePerInverseMass * rb1->GetInverseMass() };
				Vec3f move2;

				if (rb2)
				{
					move2 = movePerInverseMass * -rb2->GetInverseMass();
				}

				e1->SetPosition(e1->GetPosition() + move1);

				if (e2)
				{
					e2->SetPosition(e2->GetPosition() + move2);
				}
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

		UpdateObjects();

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
