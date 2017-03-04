#include "rigid_body_component.h"
#include "engine_context.h"

namespace Blade
{
	RigidBodyComponent::RigidBodyComponent(Entity* parent) :
		Component::Component{ "co_rb", parent }
	{
		EngineContext::GetSimulationSystem()->RegisterComponent(this);
	}


	RigidBodyComponent::~RigidBodyComponent()
	{
	}
}