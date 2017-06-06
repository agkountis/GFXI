#ifndef BLADE_XINPUTDEVICE_H_
#define BLADE_XINPUTDEVICE_H_

#include "input_device.h"

namespace Blade {

	class XInputDevice : public InputDevice
	{
		protected:
			bool Initialize() override;
	
		public:
			XInputDevice(int device_id, DeviceType devType);
			
			~XInputDevice();
			
			void Update(float deltaTime) override;
			
			bool SetVibration(float leftMotor, float rightMotor) const override;

			bool IsConnected() const override;
			
	};

}

#endif //BLADE_XINPUTDEVICE_H_
