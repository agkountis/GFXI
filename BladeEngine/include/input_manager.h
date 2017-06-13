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
	enum class JoypadNumber { JOYPAD1, JOYPAD2, JOYPAD3, JOYPAD4 };

	enum class MouseButton { LEFT = 0, RIGHT = 1 };

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
		std::map<JoypadNumber, InputDevice*> m_ActiveDevices;

		/*
		\brief Update the active devices
		*/
		void UpdateActiveDevices();

		Vec2f m_MousePos{ 0.0f }, m_MousePosPrevious{ 0.0f };
		Vec2f m_MouseMovement{ 0.0f, 0.0f };

		bool m_MouseButton[2]{ false, false };

	public:
		~InputManager();

		void SetMouseButtonState(MouseButton state, bool value);

		void UpdateMousePos(Vec2i mousepos);

		Vec2f GetAnalogStickVector(JoypadNumber player, InputSensor sensor);

		/**
		* \brief Query the keyboard device for the state of a key
		* \return True if the key is a PRESSED state (down), false otherwise
		*/
		bool QueryKeyState(VirtualKey key) const noexcept;

		/**
		* \brief Query the Keyboard device for the state of ALL keys associated to the device
		* \return True if successful, false otherwise
		*/
		bool QueryAllKeyStates(std::map<VirtualKey, bool>& destMap) const noexcept;

		/**
		* \brief Query the Keyboard device for the state of ALL keys associated to the device
		* \return True if successful, false otherwise
		*/
		Vec2f QueryMouseMovement();

		/**
		* \brief Query the Keyboard device for the state of ALL keys associated to the device
		* \return True if successful, false otherwise
		*/
		Vec2f QueryMouseMovementNormalized();

		/**
		* \brief Query the Keyboard device for the state of ALL keys associated to the device
		* \return True if successful, false otherwise
		*/
		Vec2i QueryMousePosition() const noexcept;

		/**
		* \brief Query the state of the mouse buttons (providing an enum per button)
		* \return True if pressed, false otherwise
		*/
		bool QueryMouseButtonState(MouseButton button);

		/**
		* \brief Query the state of a sensor on an active pad linked to player
		*/
		bool QueryDeviceState(JoypadNumber player, InputSensor sensor);

		/**
		* \brief Query the input states of sensors on an active device linked to player, return in supplied map
		*/
		bool QueryDeviceAllStates(JoypadNumber player, std::map<InputSensor, bool>& map);

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
		bool AssignDeviceToPlayer(JoypadNumber playerID, int deviceNumber);

		/**
		* \brief Unassigns an input device from a player (by player ID).
		* \return Destroy the association between player and device, and mark device as inactive
		*/
		bool UnassignDevice(JoypadNumber playerID);


		/**
		* \brief Returns an active (not in the pool) assigned input device, searched by player
		* \return Active input device for player id, nullptr otherwise
		*/
		InputDevice* GetActiveDevice(JoypadNumber playerID);
	};

}


#endif
