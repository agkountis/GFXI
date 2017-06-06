#pragma once
#include "input_device.h"

namespace Blade {

	class XInputDevice : public InputDevice
	{
		public:
			XInputDevice(int device_id, DeviceType devType);
			
			~XInputDevice();
			
			virtual void Update(float deltaTime);
			
			virtual bool SetVibration(float leftMotor, float rightMotor);

			bool Initialize();

			virtual bool IsConnected();
			
	};

}
