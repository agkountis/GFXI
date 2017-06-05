#include "input_device.h"

Blade::InputDevice::InputDevice()
{
}

void Blade::InputDevice::SetDeadzone(Analog_Deadzone flag, float value)
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

float Blade::InputDevice::GetDeadzone(Analog_Deadzone flag)
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

}

Blade::InputDevice::~InputDevice()
{
}
