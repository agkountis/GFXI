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
		 * \param value The key that to check.
		 * \return True if the key being queried is PRESSED (down), false otherwise
		 */
		static bool QueryKeyState(VirtualKey value) noexcept;

		/**
		 * \brief Query all virtual key states for attached keyboard
		 * \param destMap A reference to a map storing all the keyboard keys.
		 * \return True if successful, false otherwise
		 */
		static bool QueryAllKeyStates(std::map<VirtualKey, bool>& destMap) noexcept;
	};
}

#endif