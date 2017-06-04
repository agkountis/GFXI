#ifndef BLADE_INPUT_MANAGER_H_
#define BLADE_INPUT_MANAGER_H_

//If we are building for d3d -> pc version
#if defined(BLADE_BUILD_D3D)
#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#include <utility>
// required library files
#pragma comment (lib, "Xinput.lib")
#pragma comment (lib, "Xinput9_1_0.lib")

#else //Otherwise PS4 version
//PS4 stuffs here
#endif

#include <vector>
#include <map>

namespace Blade
{
	/*
	* \brief Describe the type of the device.
	*/
	enum class DeviceType { KEYBOARD, JOYPAD };

	/*
	* \brief Describe players to access devices
	*/
	enum class Player { PLAYER1, PLAYER2, PLAYER3, PLAYER4 };

	class InputDevice;
	/*
	* \brief InputManager class of the engine. This class holds and deal with all the external inputs.
	* It supports a polling function to query the current state of a joy pad and others helper functions
	* to query only the changes.
	*/
	class InputManager
	{
	private:
		/**
		* \brief The device pool stores the devices connected to the machine which can be used
		*/
		std::vector<InputDevice*> m_DevicePool;

		/**
		* \brief The active device map stores devices in use by assigned player, removed from the device pool
		*/
		std::map<Player, InputDevice*> m_ActiveDevices;

	public:

		/**
		* \brief Initialize the input manager
		* \return True if the initialization is successful, false otherwise
		*/
		bool Initialize() noexcept;

		/**
		* \brief Counts and store the number of connected devices to the machine.
		* \return An integer representing the number of connected input devices
		*/
		const int EnumerateDevices() noexcept;

		/**
		* \brief Assigns a player to an input device.
		* \return True if successful, false otherwise
		*/
		const bool AssignDeviceToPlayer(Player playerID, int deviceNumber);

		/**
		* \brief Returns an assigned input device by player
		* \return Active input device for player id, nullptr otherwise
		*/
		InputDevice* GetActiveDevice(Player playerID);

	};

}


#endif
