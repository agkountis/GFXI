#include "input_device.h"

using namespace Blade;

void InputDevice::SetInputState(const InputState & state)
{

	m_PreviousState = m_CurrentState;
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

	// Buttons - no processing; direct copy of flags
	stateOut.digitalButtonData = stateIn.digitalButtonData;
	
	// Calculate ideal neutral state for both thumbsticks
	float xShift = 0.5 * (THUMBSTICK_LIMIT_X_MAX - THUMBSTICK_LIMIT_X_MIN);
	float yShift = 0.5 * (THUMBSTICK_LIMIT_Y_MAX - THUMBSTICK_LIMIT_Y_MIN);

	// Left stick - from neutral position
	float fMagnitudeL = glm::distance(
		glm::vec2(0.0f , 0.0f),
		glm::vec2(stateIn.stickLeft.axisX - xShift, stateIn.stickLeft.axisY - yShift)
	);

	// Check against deadzone radius
	if (fMagnitudeL > DEADZONE_ASTICK_L)
	{
		// Calculate normalized position in active (not in deadzone, inside outer limit) range
		stateOut.stickLeft.axisX = (stateIn.stickLeft.axisX) / THUMBSTICK_LIMIT_X_MAX;
		stateOut.stickLeft.axisY = (stateIn.stickLeft.axisY) / THUMBSTICK_LIMIT_Y_MAX;
	}
	else {
		// The position is inside the dead zone, set to zero (no input)
		stateOut.stickLeft.axisX = 0;
		stateOut.stickLeft.axisY = 0;
	}

	// Distance from device neutral to RIGHT stick position
	float fMagnitudeR = glm::distance(
		glm::vec2(xShift, yShift),
		glm::vec2(stateIn.stickRight.axisX, stateIn.stickRight.axisY)
	);

	// Check right stick against deadzone radius
	if (fMagnitudeR > DEADZONE_ASTICK_R)
	{
		// Calculate new working zone for analog sticks (range minus dead zone)

		// Calculate normalized position in active (not in deadzone, inside outer limit) range
		fMagnitudeR -= DEADZONE_ASTICK_R;

		stateOut.stickRight.axisX = (stateIn.stickRight.axisX / STICK_THRESHOLD);
		stateOut.stickRight.axisY = (stateIn.stickRight.axisY / STICK_THRESHOLD);
	}
	else {
		// The position is inside the dead zone, set to zero (no input)
		stateOut.stickRight.axisX = 0;
		stateOut.stickRight.axisY = 0;
	}

	// Triggers - Normalize to [0.0 .. 1.0] float
	stateOut.triggerLeft = stateIn.triggerLeft / TRIGGER_THRESHOLD;
	stateOut.triggerRight = stateIn.triggerRight / TRIGGER_THRESHOLD;

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
