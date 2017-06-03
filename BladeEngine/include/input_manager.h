#ifndef BLADE_INPUT_MANAGER_H_
#define BLADE_INPUT_MANAGER_H_

//If we are building for d3d -> pc version
#if defined(BLADE_BUILD_D3D)
#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#include <utility>
// required library files
//#pragma comment (lib, "Xinput.lib")
//#pragma comment (lib, "Xinput9_1_0.lib")

#else //Otherwise PS4 version
//PS4 stuffs here
#endif

#include <vector>

namespace Blade
{
	/*
	* \brief Describe the type of the device.
	*/
	enum class DeviceType { KEYBOARD, JOYPAD };

	class InputDevice;
	/*
	* \brief InputManager class of the engine. This class holds and deal with all the external inputs.
	* It supports a polling function to query the current state of a joy pad and others helper functions
	* to query only the changes.
	*/
	class InputManager
	{
	public:

		/**
		* \brief Initialize the input manager
		* \return True if the initialization is successfully, false otherwise
		*/
		bool Initialize() noexcept;

		/**
		* \brief Counts and store the number of connected devices to the machine.
		*/
		const int EnumerateDevices() noexcept;

		/**
		* \brief The device pool stores the devices connected to the machine.
		*/
		std::vector<InputDevice*> m_DevicePool;
	};

}


#endif
