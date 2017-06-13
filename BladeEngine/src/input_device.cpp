#include "input_device.h"

using namespace Blade;

void InputDevice::SetInputState(const InputState& state)
{
	m_PreviousState = m_CurrentState;
	m_CurrentState = state;
}

Blade::InputDevice::InputDevice()
{
}

Blade::InputDevice::InputDevice(int device_id, DeviceType devType)
	: m_deviceID(device_id), m_DeviceType(devType)
{
}

void InputDevice::FilterStateData(const InputState& stateIn, InputState& stateOut)
{
	// Zero the outgoing state
	ZeroMemory(&stateOut, sizeof(InputState));

	// Buttons - no processing; direct copy of flags
	stateOut.digitalButtonData = stateIn.digitalButtonData;

	// Calculate ideal neutral state for both thumbsticks
	float xShift{ 0.5f * (THUMBSTICK_LIMIT_X_MAX - THUMBSTICK_LIMIT_X_MIN) };
	float yShift{ 0.5 * (THUMBSTICK_LIMIT_Y_MAX - THUMBSTICK_LIMIT_Y_MIN) };

	float LX{ stateIn.stickLeft.axisX };
	float LY{ stateIn.stickLeft.axisY };

	//determine how far the controller is pushed
	float magnitude{ sqrtf(LX * LX + LY * LY) };

	// Check against deadzone radius
	if (magnitude > DEADZONE_ASTICK_L)
	{
		if (magnitude > THUMBSTICK_LIMIT_X_MAX)
		{
			magnitude = THUMBSTICK_LIMIT_X_MAX;
		}

		magnitude -= DEADZONE_ASTICK_L;

		float normalizedMagnitude = magnitude / (THUMBSTICK_LIMIT_X_MAX - DEADZONE_ASTICK_L);

		stateOut.stickLeft.axisX = normalizedMagnitude * (stateIn.stickLeft.axisX / THUMBSTICK_LIMIT_X_MAX);
		stateOut.stickLeft.axisY = normalizedMagnitude * (stateIn.stickLeft.axisY / THUMBSTICK_LIMIT_Y_MAX);
	}
	else
	{
		// The position is inside the dead zone, set to zero (no input)
		stateOut.stickLeft.axisX = 0;
		stateOut.stickLeft.axisY = 0;
	}

	float RX = stateIn.stickRight.axisX;
	float RY = stateIn.stickRight.axisY;

	magnitude = sqrtf(RX * RX + RY * RY);

	// Check right stick against deadzone radius
	if (magnitude > DEADZONE_ASTICK_R)
	{
		if (magnitude > THUMBSTICK_LIMIT_X_MAX)
		{
			magnitude = THUMBSTICK_LIMIT_X_MAX;
		}

		magnitude -= DEADZONE_ASTICK_R;

		float normalizedMagnitude{ magnitude / (THUMBSTICK_LIMIT_X_MAX - DEADZONE_ASTICK_R) };

		stateOut.stickRight.axisX = normalizedMagnitude * (stateIn.stickRight.axisX / STICK_THRESHOLD);
		stateOut.stickRight.axisY = normalizedMagnitude * (stateIn.stickRight.axisY / STICK_THRESHOLD);
	}
	else
	{
		// The position is inside the dead zone, set to zero (no input)
		stateOut.stickRight.axisX = 0;
		stateOut.stickRight.axisY = 0;
	}

	// Triggers - Normalize to [0.0 .. 1.0] float
	stateOut.triggerLeft = stateIn.triggerLeft / TRIGGER_THRESHOLD;
	stateOut.triggerRight = stateIn.triggerRight / TRIGGER_THRESHOLD;
}

void InputDevice::SetDeadzone(AnalogDeadzone flag, float value)
{
	if (flag == AnalogDeadzone::ANALOG_STICK_LEFT)
	{
		// Return the left analog stick dead zone
		m_DeadZoneLeftStick = value;
	}
	else if (flag == AnalogDeadzone::ANALOG_STICK_RIGHT)
	{
		// Return the right analog stick dead zone
		m_DeadZoneRightStick = value;
	}
	else if (flag == AnalogDeadzone::ANALOG_TRIGGER)
	{
		// Return the analog trigger dead zone
		m_DeadZoneTriggers = value;
	}
}

float InputDevice::GetDeadzone(AnalogDeadzone flag) const
{
	switch (flag)
	{
	case AnalogDeadzone::ANALOG_STICK_LEFT:
		// Return the left analog stick dead zone
		return m_DeadZoneLeftStick;
	case AnalogDeadzone::ANALOG_STICK_RIGHT:
		// Return the right analog stick dead zone
		return m_DeadZoneRightStick;
	case AnalogDeadzone::ANALOG_TRIGGER:
		// Return the analog trigger dead zone
		return m_DeadZoneTriggers;
	default:
		return 0.0f;
	}
}
