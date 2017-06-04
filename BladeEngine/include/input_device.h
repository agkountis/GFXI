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
		\brief Add doc here
		*/
		virtual bool IsConnected() = 0;

		/*
		\brief Updates the active devices to 
		*/
		virtual void Update(float fDeltaTime) = 0;

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
		InputDevice();/*maybe add something here*/

		virtual ~InputDevice();

		InputDevice(const InputDevice&) = delete;

		InputDevice& operator=(const InputDevice& rhs) = delete;

		InputDevice(InputDevice&& src) = delete;

		InputDevice& operator=(InputDevice&& rhs) = delete;

	};
}


#endif