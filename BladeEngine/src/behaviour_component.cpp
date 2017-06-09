#include "behaviour_component.h"
#include "engine_context.h"

namespace Blade
{

	BehaviourComponent::BehaviourComponent(const std::string & type, Entity * parent) :
		Component(type, parent)
	{
		G_BehaviourSystem.RegisterComponent(this);
		std::cout << "Behaviour component constructor" << std::endl;
	}

	BehaviourComponent::~BehaviourComponent()
	{
		G_BehaviourSystem.UnregisterComponent(GetId());
	}

}