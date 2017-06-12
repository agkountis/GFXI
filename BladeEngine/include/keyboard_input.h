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
	private:
		/**
		 * \brief Correlate keyboard keys with a boolean flag (true if it's clicked, false otherwise)
		 */
		std::map<int, bool> m_KeyStates; // THIS IS NEVER USED. (why?)

	public:
		/**
		 * \brief Query the state of a virtual key
		 * \return True if the key being queried is PRESSED (down), false otherwise
		 */
		bool QueryKeyState(VirtualKey value) const;

		/**
		 * \brief Query all virtual key states for attached keyboard
		 * \return True if successful, false otherwise
		 */
		bool QueryAllKeyStates(std::map<VirtualKey, bool>& destMap) const;
	};
}

#endif