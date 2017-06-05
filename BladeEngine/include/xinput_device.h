#pragma once
#include "input_device.h"

namespace Blade {

	class xinput_device : public InputDevice
	{
		public:
			xinput_device();
			~xinput_device();

			virtual void Update(float deltaTime);
			
			virtual bool SetVibration(float leftMotor, float rightMotor);

	};

}
