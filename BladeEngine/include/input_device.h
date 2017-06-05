#ifndef BLADE_INPUT_DEVICE_H_
#define BLADE_INPUT_DEVICE_H_
#include "input_state.h"

#if defined(BLADE_BUILD_D3D)

#define DEADZONE_ASTICK_L	XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
#define DEADZONE_ASTICK_R	XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
#define DEADZONE_ATRIGGERS	XINPUT_GAMEPAD_TRIGGER_THRESHOLD

#elif defined(BLADE_BUILD_PS4)

/*
Updates to PS4 firmware means these values are best not to be predefined, but defined
by data from a call to scePadGetControllerInformation (returning a pad structure). These
values are for leagacy use only, and on PS4 builds, the constructor for a PS4 pad will
query the sce pad library to retrieve proper values
*/ 
#define DEADZONE_ASTICK_L	0x0d
#define DEADZONE_ASTICK_R	0x0d
#define DEADZONE_ATRIGGERS	0x0d

#else

#define DEADZONE_ASTICK_L	0x00
#define DEADZONE_ASTICK_R	0x00
#define DEADZONE_ATRIGGERS	0x00

#endif

namespace Blade
{

	enum class Analog_Deadzone {
		AnalogStickLeft,
		AnalogStickRight,
		AnalogTrigger
	};

	/*
	\brief InputDevice provides a useful abstraction for every type of device.
	*/
	class InputDevice
	{
	private:
		/*
		\brief Checks device is connected
		\return True if the device is connected and functioning, false otherwise
		*/
		virtual bool IsConnected() = 0;

		/*
		\brief The current state of the device
		*/
		InputState m_CurrentState;

		/*
		\brief The previous state of the device
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
		\brief True if the device is connected, false otherwise
		*/
		bool m_IsConnected{ false };
	public:
		/*
		\brief  Constructors and destructor of the InputDevice.
		Copy/Move operator and assignments are deleted.
		*/
		InputDevice();	/*maybe add something here*/

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
		Use AnalogStickL to set the left analog stick dead zone, AnalogStickR to set the right
		analog stick dead zone,	and AnalogTrigger to set the dead zone for both analog triggers.
		\remarks Individual trigger dead zone values are not supported
		*/
		float GetDeadzone(Analog_Deadzone flag);

		virtual ~InputDevice();

		InputDevice(const InputDevice&) = delete;

		InputDevice& operator=(const InputDevice& rhs) = delete;

		InputDevice(InputDevice&& src) = delete;

		InputDevice& operator=(InputDevice&& rhs) = delete;

	};
}


#endif