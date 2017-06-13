#include "input_component.h"
#include <iostream>
namespace Blade
{
	InputComponent::InputComponent(const std::string& type, Entity* parent):
		BehaviourComponent(type, parent)
	{
	}

	InputComponent::~InputComponent()
	{
		
	}

}