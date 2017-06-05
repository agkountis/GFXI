#include "input_manager.h"

using namespace Blade;


bool InputManager::Initialize() noexcept
{
	return true;
}

const int InputManager::EnumerateDevices() noexcept
{

	int dDevCount{ 0 };

#if defined(BLADE_BUILD_D3D)
	
	XINPUT_STATE xiState{ 0 };

	for (int i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		ZeroMemory(&xiState, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &xiState) == ERROR_SUCCESS)
		{

			++dDevCount;

			// Create a device from this and add to device pool
			// (...)

		}

	}

	return dDevCount;

#elif defined(BLADE_BUILD_PS4)

	//PS4 code here
	
	return dDevCount;
#else
	// catch-all
	return 0;
#endif
}

const bool Blade::InputManager::AssignDeviceToPlayer(Player playerID, int deviceNumber)
{

	// Exceeded bounds
	if (deviceNumber > m_DevicePool.size() || deviceNumber < 0)
	{
		return false;
	}

	// Add device to active device map
	m_ActiveDevices[playerID] = m_DevicePool[deviceNumber];

	// Remove from device pool - this device is in use
	std::vector<InputDevice*>::iterator itr = m_DevicePool.begin();
	
	std::advance(itr, deviceNumber);
	
	m_DevicePool.erase(itr);
	
	return true;
}

InputDevice * Blade::InputManager::GetActiveDevice(Player playerID)
{

	// Find by iterator
	std::map<Player, InputDevice*>::iterator itr = m_ActiveDevices.find(playerID);

	// return result or nullptr
	if (itr != m_ActiveDevices.end())
	{

		return itr->second;
		
	} 
	else {

		return nullptr;

	}

}
