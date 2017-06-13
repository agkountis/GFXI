#ifndef BLADE_KEYBOARD_INPUT_H_
#define BLADE_KEYBOARD_INPUT_H_

#include <Windows.h>
#include <map>
#include "types.h"
#include "virtual_keys.h"

namespace Blade {

	class KeyboardInput
	{
		private:
			std::map<int, bool> m_KeyStates;

		public:

			/**
			* \brief Query the state of a virtual key
			* \return True if the key being queried is PRESSED (down), false otherwise
			*/
			static bool QueryKeyState(Virtual_Key value) noexcept;

			/**
			* \brief Query all virtual key states for attached keyboard
			* \return True if successful, false otherwise
			*/
			static bool QueryAllKeyStates(std::map<Virtual_Key, bool>& destMap) noexcept;
	};

}

#endif
