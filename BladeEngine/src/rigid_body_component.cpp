#include "rigid_body_component.h"
#include "engine_context.h"

namespace Blade
{
	RigidBodyComponent::RigidBodyComponent(Entity* parent, float mass) :
		Component::Component{ "co_rb", parent },
		m_Mass{mass}
	{
		EngineContext::GetSimulationSystem()->RegisterComponent(this);
	}

	RigidBodyComponent::RigidBodyComponent(Entity * parent, float density, float volume):
		Component::Component{ "co_rb", parent },
		m_Mass{ density* volume }
	{
	}


	RigidBodyComponent::~RigidBodyComponent()
	{
		EngineContext::GetSimulationSystem()->UnregisterComponent(this);
	}

	void RigidBodyComponent::AddForce(Vec3d & f) noexcept
	{
		m_Velocity += f;
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