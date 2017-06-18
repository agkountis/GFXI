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
	* \brief Describe joypad number
	*/
	enum class JoypadNumber { JOYPAD1, JOYPAD2, JOYPAD3, JOYPAD4 };

	/*
	\brief Describe the mouse button. 
	*/
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

		/*
		\brief The mouse position.
		*/
		Vec2f m_MousePos{ 0.0f };

		/*
		\brief The previous mouse position.
		*/
		Vec2f m_MousePosPrevious{ 0.0f };

		/*
		\brief The amount of change of mouse movement between an update and another.
		*/
		Vec2f m_MouseMovement{ 0.0f, 0.0f };

		/*
		\brief The mouse buttons. 
		*/
		bool m_MouseButton[2]{ false, false };

	public:
		/*
		\brief The input manager destructor.
		*/
		~InputManager();

		/**
		* \brief Returns a vector indicating the position of the analog stick requested.
		* \param joypadNumber The joypad number.
		* \param sensor The stick that need to be checked
		* \return The vector that represent the stick position normalized outside dead zones.
		*/
		Vec2f GetAnalogStickVector(JoypadNumber joypadNumber, InputSensor sensor);

		/**
		* \brief Query the keyboard device for the state of a key
		* \param key A keyboard key.
		* \return True if the key is a PRESSED state (down), false otherwise
		*/
		bool QueryKeyState(VirtualKey key) const noexcept;

		/**
		* \brief Query the Keyboard device for the state of ALL keys associated to the device
		* \param map The reference to a map of all keyboard states. 
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
		* \param button The mouse button 
		* \return True if pressed, false otherwise
		*/
		bool QueryMouseButtonState(MouseButton button);

		/**
		* \brief Query the state of a sensor on an active pad linked
		* \param joypadNumber The queried joypad number
		* \param sensor The sensor to check
		* \return TRUE if the the sensor is active (button pressed, stick out of the deadzone), FALSE otherwise.
		*/
		bool QueryDeviceState(JoypadNumber joypadNumber, InputSensor sensor);

		/**
		* \brief Query the input states of sensors on an active device linked to player, return in supplied map
		* \param joypadNumber The queried joypad number.
		* \param map  A reference to a map of the state of the joypad.
		* \return TRUE if the JoypadNumber is active, false otherwise
		*/
		bool QueryDeviceAllStates(JoypadNumber joypadNumber, std::map<InputSensor, bool>& map);

		/**
		* \brief Update the states of managed input devices, and re-enumerate input devices
		* \param deltaTime The delta time.
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
		* \param deviceId The device number.
		* \return DeviceType enum of the device in the pool denoted by devIndex
		* \remarks If the device is not found, or an error has occurred, DEVTYPE_ERROR is returned
		*/
		DeviceType DevicePoolQueryType(int deviceId);

		/**
		* \brief Search the device pool for a device with id equal to deviceId
		* \param deviceID The device number.
		* \return True if the device is found, otherwise false
		*/
		bool PooledDeviceExists(int deviceId);

		/**
		* \brief Search the active device map for a device with id equal to deviceId
		* \param deviceId The device number you need to find in the map.
		* \return True if the device is found, otherwise false
		*/
		bool ActiveDeviceExists(int deviceId);

		/**
		* \brief Assigns a player to an input device.
		* \param joypadNumber The joy pad number.
		* \param deviceNumber The number of the device from the pool.
		* \return True if successful, false otherwise
		*/
		bool AssignDeviceToPlayer(JoypadNumber joypadNumber, int deviceNumber);

		/**
		* \brief Unassigns an input device from a player (by player ID)
		* \param joypadNumber The number of the joy pad player number.
		* \return Destroy the association between player and device, and mark device as inactive
		*/
		bool UnassignDevice(JoypadNumber joypadNumber);


		/**
		* \brief Returns an active (not in the pool) assigned input device, searched by player
		* \param joypadNumber The number of the joy pad number.
		* \return Active input device for player id, nullptr otherwise
		*/
		InputDevice* GetActiveDevice(JoypadNumber joypadNumber);


		/*
		\brief Update the position of the mouse.
		\param mousepos A vector that represents the mouse position relative to window.
		\details This method is been called inside the window update loop.
		*/
		void UpdateMousePos(Vec2i mousepos);

		/*
		\brief Update the state of a button of the mouse.
		\param state The button of the mouse that has changed (left of right)
		\param value The boolean value associate with that flag: TRUE pressed.
		\details This method is been called inside the window update loop.
		*/
		void SetMouseButtonState(MouseButton state, bool value);
	};

}


#endif
