#include "input_manager.h"

using namespace Blade;

bool InputManager::Initialize() noexcept
{
#if defined(BLADE_BUILD_D3D)

	// XInput is already initialized

#elif defined(BLADE_BUILD_PS4)

	// init PS4 pad library
	if (scePadInit() != SCE_OK) {

		std::cerr << "PS4 Pad library failed to initialize" << std::endl;
		
		return false;

	}

#endif

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

			// Device shows as connected/active - create a new xinputdevice
			
			XInputDevice* xDev = new XInputDevice(i, DeviceType::Joypad);

			// Add the new device to the pool

			m_DevicePool.push_back(xDev);

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


DeviceType Blade::InputManager::DevicePoolQueryType(int deviceId)
{

	InputDevice* tmpDev{ nullptr };

	// Search for device_id
	for (unsigned int i = 0; (i < m_DevicePool.size()); i++) {

		tmpDev = m_DevicePool[i];

		if (tmpDev->GetDeviceID() == deviceId) {

			return tmpDev->GetDeviceType();

		}

	}

	// Not found
	return DeviceType::DEVTYPE_ERROR;
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

	// Remove from device pool - this device is now in use
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

Blade::InputManager::~InputManager()
{

	// invalidate and release active input devices

	std::map<Player, InputDevice*>::iterator itrActive = m_ActiveDevices.begin();

	InputDevice* tempDevice{ nullptr };

	for (itrActive = m_ActiveDevices.begin(); itrActive != m_ActiveDevices.end(); ++itrActive)
	{

		tempDevice = itrActive->second;

		// remove from map
		m_ActiveDevices.erase(itrActive);

		// delete object
		delete tempDevice;

	}
		

	// invalidate and release inactive devices in the device pool

	std::vector<InputDevice*>::iterator itrPool = m_DevicePool.begin();

	tempDevice = nullptr;

	for (itrPool = m_DevicePool.begin(); itrPool != m_DevicePool.end(); ++itrPool)
	{

		tempDevice = *itrPool;

		// remove from pool
		m_DevicePool.erase(itrPool);

		// delete object
		delete tempDevice;

	}

}
