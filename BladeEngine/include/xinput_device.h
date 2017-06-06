#pragma once
#include "input_device.h"

namespace Blade {

	class xinput_device : public InputDevice
	{
		public:
			xinput_device(int device_id, DeviceType devType);

			virtual void Update(float deltaTime);
			
			virtual bool SetVibration(float leftMotor, float rightMotor);

	};

}
