#ifndef BLADE_INPUT_DEVICE_H_
#define BLADE_INPUT_DEVICE_H_
#include "input_state.h"

#if defined(BLADE_BUILD_D3D)

#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#include <utility>

// required library files
#pragma comment (lib, "Xinput.lib")
#pragma comment (lib, "Xinput9_1_0.lib")

#elif defined (BLADE_BUILD_PS4)

#include <pad.h>

#endif

/*
\brief The delta tolerance between states of an analog sensor before a change is recognized. Normalized to [0.0...1.0]
*/
#define ANALOG_DELTA		0.05f

#if defined(BLADE_BUILD_D3D)

#define DEADZONE_ASTICK_L	XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
#define DEADZONE_ASTICK_R	XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
#define DEADZONE_ATRIGGERS	XINPUT_GAMEPAD_TRIGGER_THRESHOLD
#define VIBRATION_THRESHOLD	65535

#elif defined(BLADE_BUILD_PS4)

/*
Updates to PS4 firmware means these values are best not to be predefined, but defined
by data from a call to scePadGetControllerInformation (returning a pad structure). These
values are for leagacy use only.
*/ 
#define DEADZONE_ASTICK_L	0x0d
#define DEADZONE_ASTICK_R	0x0d
#define DEADZONE_ATRIGGERS	0x0d
#define VIBRATION_THRESHOLD	255

#else

// ignore values?
#define DEADZONE_ASTICK_L	0x00
#define DEADZONE_ASTICK_R	0x00
#define DEADZONE_ATRIGGERS	0x00

#endif

namespace Blade
{
	/*
	* \brief Describe the type of the device.
	*/
	enum class DeviceType {
		Keyboard,
		Joypad,
		Other,
		DEVTYPE_ERROR
	};

	enum class Analog_Deadzone {
		AnalogStickLeft,
		AnalogStickRight,
		AnalogTrigger
	};

	/*
	\brief InputDevice provides a useful abstraction for every type of input device.
	*/
	class InputDevice
	{
	private:

		int m_deviceID{ -1 };

		/*
		\brief The most recent recorded state of the device
		*/
		InputState m_CurrentState;

		/*
		\brief The state of the device one polling event before the current recorded state
		*/
		InputState m_PreviousState;

		/*
		\brief Deadzone value for left analog stick
		*/
		float m_DeadZoneLeftStick{ DEADZONE_ASTICK_L };

		/*
		\brief Deadzone value for left analog stick
		*/
		float m_DeadZoneRightStick{ DEADZONE_ASTICK_R };

		/*
		\brief Deadzone value for analog triggers
		*/
		float m_DeadZoneTriggers{ DEADZONE_ATRIGGERS };

		/*
		\brief Enumeration of device type
		*/
		DeviceType m_DeviceType{ DeviceType::DEVTYPE_ERROR };

	protected:

		/*
		\brief Gets the device ID (input API handle)
		*/
		void SetDeviceID(int id) { m_deviceID = id; }

		/*
		\brief Sets the type of the device
		*/
		void SetDeviceType(DeviceType devType) { m_DeviceType = devType; }

		/*
		\brief Gets the last (newest) buffered input state to read
		*/
		const InputState& GetCurrentState() { return m_CurrentState; }

		/*
		\brief Gets the previous buffered previous input state to read
		*/
		const InputState& GetPreviousState() {	return m_PreviousState;	}

		/*
		\brief Moves the newest input state to the previous state and stores the provided state as newest
		*/
		void SetInputState(const InputState& state);

		/*
		\brief Initialize the selected InputDevice
		\details Allocates any needed resources and handles to use the device, and prepares it to a ready state
		\remarks Any pre-initialization and resource allocation to be able to immediately use the device is performed here
		\return True if successful, false otherwise
		*/
		virtual bool Initialize() = 0;

	public:

		InputDevice();
		
		/*
		\brief  Constructors and destructor of the InputDevice.
		Copy/Move operator and assignments are deleted.
		*/
		InputDevice(int device_id, DeviceType devType);

		/*
		\brief Gets the device ID (input API handle)
		*/
		int GetDeviceID() { return m_deviceID; }

		/*
		\brief Updates the active devices to the latest input states available and buffers the most recent previous state
		*/
		virtual void Update(float fDeltaTime) = 0;

		/*
		\brief Sets vibration parameters of input device (if supported)
		\details Left and right motors are set independently from 0.0 (off) to 1.0 (100%)
		\return True if successful, false otherwise
		*/
		virtual bool SetVibration(float leftMotor, float rightMotor) = 0;

		/*
		\brief Set dead zone information for an analog sensor on the the device (stick, trigger, etc)
		\details Overrides the pre-defined DEADZONE_ASTICKL/DEADZONE_ASTICKR/DEADZONE_ATRIGGERS values
		\remarks The flag enum is of type Analog_Deadzone, and represents which value to update.
		Use AnalogStickL to set the left analog stick dead zone, AnalogStickR to set the right 
		analog stick dead zone,	and AnalogTrigger to set the dead zone for both analog triggers.
		\remarks Individual trigger dead zone values are not supported
		*/
		void SetDeadzone(Analog_Deadzone flag, float value);

		/*
		\brief Get dead zone information for an analog sensor on the the device (stick, trigger, etc)
		\remarks The flag enum is of type Analog_Deadzone, and represents which value to update.
		Use AnalogStickL to get the left analog stick dead zone, AnalogStickR to get the right
		analog stick dead zone,	and AnalogTrigger to get the dead zone for both analog triggers.
		\remarks Individual trigger dead zone values are not supported
		*/
		float GetDeadzone(Analog_Deadzone flag);

		/*
		\brief Checks device is connected
		\return True if the device is connected and functioning, false otherwise
		*/
		virtual bool IsConnected() = 0;

		/*
		\brief Get the type of device
		\return Enum of DeviceType of the device if successful, DeviceType enum DEVTYPE_ERROR otherwise
		*/
		DeviceType GetDeviceType() { return m_DeviceType; }

		virtual ~InputDevice();

		InputDevice(const InputDevice&) = delete;

		InputDevice& operator=(const InputDevice& rhs) = delete;

		InputDevice(InputDevice&& src) = delete;

		InputDevice& operator=(InputDevice&& rhs) = delete;

	};
}


#endif