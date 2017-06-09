#include "input_component.h"

namespace Blade
{
	InputComponent::InputComponent(const std::string& type, Entity* parent):
		BehaviourComponent(type, parent)
	{
		//Do we need to store all the systems to a particular system? no
	}

	InputComponent::~InputComponent()
	{
		
	}

}