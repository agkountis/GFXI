#include "input_device.h"

using namespace Blade;

void InputDevice::SetInputState(const InputState & state)
{
	m_PreviousState = m_CurrentState;
	m_CurrentState = state;
}

InputDevice::InputDevice()
{
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
