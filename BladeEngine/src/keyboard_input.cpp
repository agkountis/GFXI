#include "keyboard_input.h"

namespace Blade
{
	bool KeyboardInput::QueryKeyState(VirtualKey value) const
	{

		return ((GetKeyState(value) & 0x8000) != 0);

	}

	bool KeyboardInput::QueryAllKeyStates(std::map<VirtualKey, bool>& destMap) const
	{
		BYTE keyState[256] = { 0 };
		GetKeyboardState(keyState);

		for (auto entry : keyState)
		{
			// convert to virtual key
			VirtualKey vk = static_cast<VirtualKey>(entry);

			// get high order bit to check if pressed
			destMap[vk] = (entry & 0x8000) != 0;

		}

		return false;
	}
}
