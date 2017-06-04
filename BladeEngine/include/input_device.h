#ifndef BLADE_INPUT_DEVICE_H_
#define BLADE_INPUT_DEVICE_H_
#include "input_state.h"

namespace Blade
{
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

		virtual ~InputDevice();

		InputDevice(const InputDevice&) = delete;

		InputDevice& operator=(const InputDevice& rhs) = delete;

		InputDevice(InputDevice&& src) = delete;

		InputDevice& operator=(InputDevice&& rhs) = delete;

	};
}


#endif