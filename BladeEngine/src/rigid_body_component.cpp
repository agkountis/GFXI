#include "rigid_body_component.h"
#include "engine_context.h"

namespace Blade
{
	RigidBodyComponent::RigidBodyComponent(Entity* parent, float mass) :
		Component::Component{ "co_rb", parent },
		m_Mass{mass}
	{
		G_SimulationSystem.RegisterComponent(this);
	}

	RigidBodyComponent::RigidBodyComponent(Entity * parent, float density, float volume):
		Component::Component{ "co_rb", parent },
		m_Mass{ density* volume }
	{
	}

	RigidBodyComponent::~RigidBodyComponent()
	{
		G_SimulationSystem.UnregisterComponent(this);
	}

	void RigidBodyComponent::AddForce(Vec3d & force) noexcept
	{
		m_Velocity += force;
	}

	Vec3d RigidBodyComponent::GetVelocity() const noexcept
	{
		return m_Velocity;
	}

	float RigidBodyComponent::GetMass() const noexcept
	{
		return m_Mass;
	}

}