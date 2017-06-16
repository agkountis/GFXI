#include "input_component.h"
#include <iostream>
namespace Blade
{
	InputComponent::InputComponent(const std::string& type, Entity* parent, bool online):
		BehaviourComponent(type, parent), m_Online{online}
	{
	}

	InputComponent::~InputComponent()
	{
		
	}

}