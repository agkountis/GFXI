#include "joypad_input_component.h"

namespace Blade
{
	JoypadInputComponent::JoypadInputComponent(const std::string & type, Entity * parent, Player player):
		InputComponent(type, parent),m_Player(player)
	{

	}

	JoypadInputComponent::~JoypadInputComponent()
	{
		//Clear the map since we're using shared pointers it should reduce the counter of the 
		//commands. Need to test the ref-counter of each object
		m_JoypadCommandMap.clear();
	}
	bool JoypadInputComponent::LoadConfiguration(const std::vector<JOYPAD_ENUM>& control, const std::vector<std::shared_ptr<Command>>& commands) noexcept
	{
		if (control.size() == commands.size())
		{
			for (size_t i{ 0 }; i < control.size(); ++i)
			{
				m_JoypadCommandMap[control[i]] = commands[i];
			}
			return true;
		}
		return false;
	}
	bool JoypadInputComponent::LoadConfiguration(const JoypadCommandMap & map)
	{
		m_JoypadCommandMap = map;
		return true;
	}
}