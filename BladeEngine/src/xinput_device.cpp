#include "xinput_device.h"

using namespace Blade;

xinput_device::xinput_device()
{
}

xinput_device::~xinput_device()
{
}

void xinput_device::Update(float deltaTime)
{
	// Update the input states
	XINPUT_STATE tmpState;
	ZeroMemory(&tmpState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD result = XInputGetState(GetDeviceID(), &tmpState);
		

}

bool xinput_device::SetVibration(float leftMotor, float rightMotor)
{
	XINPUT_VIBRATION vibParams;
	ZeroMemory(&vibParams, sizeof(XINPUT_VIBRATION));

	// multiply up from normalised value to xinput thresholds
	vibParams.wLeftMotorSpeed = static_cast<int>(leftMotor * VIBRATION_THRESHOLD);
	
	vibParams.wRightMotorSpeed = static_cast<int>(leftMotor * VIBRATION_THRESHOLD);

	DWORD result = XInputSetState(GetDeviceID(), &vibParams);

	return (result == ERROR_SUCCESS);
}
