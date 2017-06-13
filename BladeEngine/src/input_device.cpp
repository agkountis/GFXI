#include "input_device.h"

using namespace Blade;

void InputDevice::SetInputState(const InputState & state)
{

	// Store the current stored state as previous
	m_PreviousState = m_CurrentState;
	// Store the new state as current
	m_CurrentState = state;

}

Blade::InputDevice::InputDevice()
{
}

Blade::InputDevice::InputDevice(int device_id, DeviceType devType) : m_deviceID(device_id), m_DeviceType(devType)
{
}

void InputDevice::FilterStateData(const InputState& stateIn, InputState& stateOut) const
{

	// Zero the outgoing state
	ZeroMemory(&stateOut, sizeof(InputState));

	// Buttons - no processing; Pass through
	stateOut.digitalButtonData = stateIn.digitalButtonData;

	// Calculate ideal neutral state for both thumbsticks
	float xShift = 0.5 * (THUMBSTICK_LIMIT_X_MAX - THUMBSTICK_LIMIT_X_MIN);
	float yShift = 0.5 * (THUMBSTICK_LIMIT_Y_MAX - THUMBSTICK_LIMIT_Y_MIN);

	float LX = stateIn.stickLeft.axisX;
	float LY = stateIn.stickLeft.axisY;

	//determine the magnitude of the position
	float magnitude = sqrt(LX*LX + LY*LY);

	// Check against deadzone radius
	if (magnitude > DEADZONE_ASTICK_L)
	{

		// Clamp if exceeded maximum range
		if (magnitude > THUMBSTICK_LIMIT_X_MAX) {

			magnitude = THUMBSTICK_LIMIT_X_MAX;

		}

		magnitude -= DEADZONE_ASTICK_L;

		float normalizedMagnitude = magnitude / (THUMBSTICK_LIMIT_X_MAX - DEADZONE_ASTICK_L);

		stateOut.stickLeft.axisX = normalizedMagnitude * (stateIn.stickLeft.axisX / THUMBSTICK_LIMIT_X_MAX);
		stateOut.stickLeft.axisY = normalizedMagnitude * (stateIn.stickLeft.axisY / THUMBSTICK_LIMIT_Y_MAX);
	}
	else {
		// The position is inside the dead zone, set to zero (no input)
		stateOut.stickLeft.axisX = 0;
		stateOut.stickLeft.axisY = 0;
	}

	float RX = stateIn.stickRight.axisX;
	float RY = stateIn.stickRight.axisY;

	magnitude = sqrt(RX * RX + RY * RY);

	// Check right stick against deadzone radius
	if (magnitude > DEADZONE_ASTICK_R)
	{
		if (magnitude > THUMBSTICK_LIMIT_X_MAX) {

			magnitude = THUMBSTICK_LIMIT_X_MAX;

		}

		magnitude -= DEADZONE_ASTICK_R;

		float normalizedMagnitude = magnitude / (THUMBSTICK_LIMIT_X_MAX - DEADZONE_ASTICK_R);

		stateOut.stickRight.axisX = normalizedMagnitude * (stateIn.stickRight.axisX / STICK_THRESHOLD);
		stateOut.stickRight.axisY = normalizedMagnitude * (stateIn.stickRight.axisY / STICK_THRESHOLD);
	}
	else {
		// The position is inside the dead zone, set to zero (no input)
		stateOut.stickRight.axisX = 0;
		stateOut.stickRight.axisY = 0;
	}

	// Apply deadzones and normalize triggers to working range minus deadzone
	stateOut.triggerLeft = (stateIn.triggerLeft > DEADZONE_ATRIGGERS) ? static_cast<float>(stateIn.triggerLeft / (TRIGGER_THRESHOLD - DEADZONE_ATRIGGERS)) : 0.0f;
	stateOut.triggerRight = (stateIn.triggerRight > DEADZONE_ATRIGGERS) ? static_cast<float>(stateIn.triggerRight / (TRIGGER_THRESHOLD - DEADZONE_ATRIGGERS)) : 0.0f;

}

void InputDevice::SetDeadzone(Analog_Deadzone flag, float value)
{

	if (flag == Analog_Deadzone::AnalogStickLeft)
	{

		// Return the left analog stick dead zone
		m_DeadZoneLeftStick = value;

	}
	else if (flag == Analog_Deadzone::AnalogStickRight)
	{

		// Return the right analog stick dead zone
		m_DeadZoneRightStick = value;

	}
	else if (flag == Analog_Deadzone::AnalogTrigger)
	{

		// Return the analog trigger dead zone
		m_DeadZoneTriggers = value;

	}

}

float InputDevice::GetDeadzone(Analog_Deadzone flag)
{

	if (flag == Analog_Deadzone::AnalogStickLeft)
	{

		// Return the left analog stick dead zone
		return m_DeadZoneLeftStick;

	}
	else if (flag == Analog_Deadzone::AnalogStickRight)
	{

		// Return the right analog stick dead zone
		return m_DeadZoneRightStick;

	}
	else if (flag == Analog_Deadzone::AnalogTrigger)
	{

		// Return the analog trigger dead zone
		return m_DeadZoneTriggers;

	}

	return 0.0f;

}

InputDevice::~InputDevice()
{
}
