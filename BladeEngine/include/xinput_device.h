#ifndef BLADE_XINPUTDEVICE_H_
#define BLADE_XINPUTDEVICE_H_

#include "input_device.h"

namespace Blade {

	class XInputDevice : public InputDevice
	{
		protected:
			/**
			* \brief Perform any initialization of the input device (allocation of resources, etc)
			* \return True if successful, false otherwise
			*/
			bool Initialize() override;
	
		public:
			/**
			* \brief Initializes the device with an identifier and type of device
			*/
			XInputDevice(int device_id, DeviceType devType);
			
			~XInputDevice();
			
			/**
			* \brief Update the device input state by polling the device
			* \return Requests the newest data from the device, normalizes the information and stores the information in the most recent InputState structure
			*/
			void Update(float deltaTime) override;
			
			/**
			* \brief Set the vibration parameters of the input device
			* \details The xinput-compatible device has two vibration motors which can be set in a range to vibrate from none (zero) to full (1.0)
			* \return True if the key being queried is PRESSED (down), false otherwise
			*/
			bool SetVibration(float leftMotor, float rightMotor) const override;

			/**
			* \brief Returns the device's connected status
			* \return True if the device is connected and functional, false otherwise
			*/
			bool IsConnected() const override;
			
	};

}

#endif //BLADE_XINPUTDEVICE_H_
