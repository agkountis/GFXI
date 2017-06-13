#ifndef BLADE_KEYBOARD_INPUT_H_
#define BLADE_KEYBOARD_INPUT_H_
#include <map>
#include "virtual_keys.h"

namespace Blade
{
	/**
	 * \brief Keyboard abstraction of the engine.
	 */
	class KeyboardInput
	{

	public:
		/**
		 * \brief Query the state of a virtual key
		 * \return True if the key being queried is PRESSED (down), false otherwise
		 */
		static bool QueryKeyState(VirtualKey value) noexcept;

		/**
		 * \brief Query all virtual key states for attached keyboard
		 * \return True if successful, false otherwise
		 */
		static bool QueryAllKeyStates(std::map<VirtualKey, bool>& destMap) noexcept;
	};
}

#endif