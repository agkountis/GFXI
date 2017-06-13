#include "keyboard_input_component.h"

namespace Blade
{
	KeyboardInputComponent::KeyboardInputComponent( Entity * parent)
		:InputComponent("co_kic",parent)
	{
	}
	KeyboardInputComponent::~KeyboardInputComponent()
	{
		//Clear the map since we're using shared pointers it should reduce the counter of the 
		//commands. Need to test the ref-counter of each object
		m_KeyboardCommandMap.clear();
	}
	bool KeyboardInputComponent::LoadConfiguration(std::vector<VirtualKey>& keys, const std::vector<std::shared_ptr<Command>>& commands) noexcept
	{
		if (keys.size() == commands.size())
		{
			for (size_t i{ 0 }; i < keys.size(); ++i)
			{
				m_KeyboardCommandMap[keys[i]] = commands[i];
			}
			return true;
		}
		return false;
	}
	bool KeyboardInputComponent::LoadConfiguration(const KeyboardCommandMap & map)
	{
		m_KeyboardCommandMap = map;
		return true;
	}
}