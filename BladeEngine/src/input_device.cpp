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

	// Calculate ideal neutral state for both thumbsticks (assumption that both use same values)
	int iDefaultStickX = (THUMBSTICK_LIMIT_X_MIN + THUMBSTICK_LIMIT_X_MAX) * 0.5f;
	int iDefaultStickY = (THUMBSTICK_LIMIT_Y_MIN + THUMBSTICK_LIMIT_Y_MAX) * 0.5f;

	// Distance from device neutral to LEFT stick position
	float fDistance = glm::distance(
		glm::vec2(iDefaultStickX, iDefaultStickY),
		glm::vec2(stateIn.stickLeft.axisX, stateIn.stickLeft.axisY)
	);

	// Check left stick against deadzone radius
	if (fDistance > DEADZONE_ASTICK_L)
	{
		// Calculate new working zone for analog sticks (range minus dead zone)
	}
	else {
		// The position is inside the dead zone, set to zero (no input)
		stateOut.stickLeft.axisX = 0;
		stateOut.stickLeft.axisY = 0;
	}

	// Distance from device neutral to RIGHT stick position
	fDistance = glm::distance(
		glm::vec2(iDefaultStickX, iDefaultStickY),
		glm::vec2(stateIn.stickRight.axisX, stateIn.stickRight.axisY)
	);

	// Check right stick against deadzone radius
	if (fDistance > DEADZONE_ASTICK_R)
	{
		// Calculate new working zone for analog sticks (range minus dead zone)

	}
	else {
		// The position is inside the dead zone, set to zero (no input)
		stateOut.stickRight.axisX = 0;
		stateOut.stickRight.axisY = 0;
	}

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
