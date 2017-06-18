#ifndef BLADE_XINPUTDEVICE_H_
#define BLADE_XINPUTDEVICE_H_

#include "input_device.h"

namespace Blade
{
	/*
	\brief XInput Device class.
	*/
	class XInputDevice : public InputDevice
	{
	protected:
		/*
		\brief Initialize the XInputDevice
		\return TRUE if the initialization succeed, false otherwise.
		*/
		bool Initialize() override;

	public:
		/*
		\brief The XInputDevice constructor
		\param device_id The device ID 
		\param devType The type of the device.
		*/
		XInputDevice(int device_id, DeviceType devType);

		~XInputDevice() = default;

		/*
		\brief Update the XInputDevice state
		\param deltaTime The delta time.
		*/
		void Update(float deltaTime) override;

		/*
		\brief Set the vibration of the controller
		\param leftMotor Amount of the left motor vibration.
		\param rightMotor Amount of the right motor vibration.
		\return TRUE if vibration supported, FALSE otherwise.
		*/
		bool SetVibration(float leftMotor, float rightMotor) const override;

		/*
		\brief Check the XInput joypad is connected
		\return TRUE if the XInput joypad is connected, FALSE otherwise.
		*/
		bool IsConnected() const override;
	};
}

#endif //BLADE_XINPUTDEVICE_H_
