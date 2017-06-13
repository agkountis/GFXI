#include "keyboard_input.h"

using namespace Blade;

bool KeyboardInput::QueryKeyState(Virtual_Key value) noexcept
{
	return ( (GetKeyState(value) & 0x8000) != 0 );
}

bool KeyboardInput::QueryAllKeyStates(std::map<Virtual_Key, bool>& destMap) noexcept
{
	BYTE keyState[256] = { 0 };
	GetKeyboardState(keyState);

	for (auto entry : keyState)
	{
		// convert to virtual key
		Virtual_Key vk = static_cast<Virtual_Key>(entry);

		// get high order bit to check if pressed
		destMap[vk] = ((entry & 0x8000) != 0);

	}

	return false;
}
