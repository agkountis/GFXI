#ifndef BLADE_INPUT_MANAGER_H_
#define BLADE_INPUT_MANAGER_H_

//If we are building for d3d -> pc version
#if defined(BLADE_BUILD_D3D)

#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#include <utility>

#include "trace.h"
#include "xinput_device.h"
#include "input_state.h"
#include "keyboard_input.h"
#include "types.h"

// required library files
#pragma comment (lib, "Xinput.lib")
#pragma comment (lib, "Xinput9_1_0.lib")

#elif defined (BLADE_BUILD_PS4)

// include ps4 type inputdevice header here
#include <pad.h>

#endif

#include <vector>
#include <map>

namespace Blade
{

	/*
	* \brief Describe players to access devices
	*/
	enum class Player { PLAYER1, PLAYER2, PLAYER3, PLAYER4 };

	class InputDevice;
	/*
	* \brief InputManager class of the engine. This class holds and deals with all the external inputs.
	* It supports a polling function to query the current state of a joypad and other helper functions
	* to find the change in states between updates.
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

		KeyboardInput	m_Keyboard;

	public:

		/**
		* \brief Return the vector of a simulated analog stick from keyboard
		* \return 2 part float vector of state, otherwise a 2-part vector of [0,0], meaning no input
		*/
		//Vec2f GetKeyboardInputVector(std::vector<Virtual_Key>& keys);

		/**
		* \brief Return the vector of an analog stick from the active device linked to [player]
		* \return 2 part float vector of stick state, otherwise a 2-part vector of [0,0], meaning no input
		*/
		Vec2f GetAnalogStickVector(Player player, Input_Sensor sensor);

		/**
		* \brief Query the keyboard device for the state of a key
		* \return True if the key is a PRESSED state (down), false otherwise
		*/
		bool QueryKeyState(Virtual_Key key) { return m_Keyboard.QueryKeyState(key); }

		/**
		* \brief Query the Keyboard device for the state of ALL keys associated to the device
		* \return True if successful, false otherwise
		*/
		bool QueryAllKeyStates(std::map<Virtual_Key, bool>& destMap) { return m_Keyboard.QueryAllKeyStates(destMap); }

		/**
		* \brief Query the state of a sensor on an active pad linked to player
		*/
		bool QueryDeviceState(Player player, Input_Sensor sensor);

		/**
		* \brief Query the input states of sensors on an active device linked to player, return in supplied map
		*/
		bool QueryDeviceAllStates(Player player, std::map<Input_Sensor, bool>& map);

		/**
		* \brief Update the states of managed input devices, and re-enumerate input devices
		*/
		void Update(float deltaTime);

		/**
		* \brief Initialize the input manager
		* \return True if the initialization is successful, false otherwise
		*/
		bool Initialize() noexcept;

		/**
		* \brief Counts and store the number of connected devices to the machine.
		* \return An integer representing the number of connected input devices
		*/
		int EnumerateDevices() noexcept;

		/**
		* \brief Query a device pool for its type
		* \return DeviceType enum of the device in the pool denoted by devIndex
		* \remarks If the device is not found, or an error has occurred, DEVTYPE_ERROR is returned
		*/
		DeviceType DevicePoolQueryType(int deviceId);

		/**
		* \brief Search the device pool for a device with id equal to deviceId
		* \return True if the device is found, otherwise false
		*/		
		bool PooledDeviceExists(int deviceId);

		/**
		* \brief Search the active device map for a device with id equal to deviceId
		* \return True if the device is found, otherwise false
		*/		
		bool ActiveDeviceExists(int deviceId);

		/**
		* \brief Assigns a player to an input device.
		* \return True if successful, false otherwise
		*/
		bool AssignDeviceToPlayer(Player playerID, int deviceNumber);

		/**
		* \brief Unassigns an input device from a player (by player ID).
		* \return Destroy the association between player and device, and mark device as inactive
		*/
		bool UnassignDevice(Player playerID);


		/**
		* \brief Returns an active (not in the pool) assigned input device, searched by player
		* \return Active input device for player id, nullptr otherwise
		*/
		InputDevice* GetActiveDevice(Player playerID);

		~InputManager();

	};

}


#endif
