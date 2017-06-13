#include "xinput_device.h"

using namespace Blade;

XInputDevice::XInputDevice(int device_id, DeviceType devType)
{

	// Set the device id
	SetDeviceID(device_id);

	// Set the device type
	SetDeviceType(devType);

}

XInputDevice::~XInputDevice()
{

	// XInput does not require any shutdown procedure

}

void XInputDevice::Update(float deltaTime)
{

	// Update the input states
	XINPUT_STATE tmpState;
	ZeroMemory(&tmpState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD result = XInputGetState(GetDeviceID(), &tmpState);

	// Create an input state from the raw XINPUT data
	InputState rawState(tmpState);

	// filter the state into another
	InputState filteredState;
	FilterStateData(rawState, filteredState);
	
	// Store the filtered state (move current newest to previous, store newState as current)
	SetInputState(filteredState);

}

bool XInputDevice::SetVibration(float leftMotor, float rightMotor) const
{

	// Structure to hold vibration information
	XINPUT_VIBRATION vibParams;
	ZeroMemory(&vibParams, sizeof(XINPUT_VIBRATION));

	// scale to xinput range [0..1]-->[0..65536]
	vibParams.wLeftMotorSpeed = static_cast<int>(leftMotor * VIBRATION_THRESHOLD);
	vibParams.wRightMotorSpeed = static_cast<int>(rightMotor * VIBRATION_THRESHOLD);
	
	// Perform the Set operation using vibParams
	DWORD result = XInputSetState(GetDeviceID(), &vibParams);

	// Status of XInputSetState as boolean
	return (result == ERROR_SUCCESS);

}

bool Blade::XInputDevice::Initialize()
{

	// XInput devices are already initialised. Return true as default
	return true;
}

bool Blade::XInputDevice::IsConnected() const
{

	/*
	* XInput requires the API to be polled (using the device index) to return
	* the operating state of the controller (and if successful, a state of the sensors)
	*/

	// Prepare a state to hold information
	XINPUT_STATE tmpState;
	ZeroMemory(&tmpState, sizeof(XINPUT_STATE));

	// Query the state
	DWORD result = XInputGetState(GetDeviceID(), &tmpState);

	// Return state
	return (result != ERROR_DEVICE_NOT_CONNECTED);

}
