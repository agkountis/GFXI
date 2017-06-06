#include "input_manager.h"

using namespace Blade;

void Blade::InputManager::Update(float deltaTime)
{

	// re-enumerate input API for any newly connected devices since the last check
	int result = EnumerateDevices();

	InputDevice* tempDev{ nullptr };

	std::map<Player, InputDevice*>::iterator itr = m_ActiveDevices.begin();

	// Update the state of active input devices (in the active map, with player assignments)
	for (itr = m_ActiveDevices.begin(); itr != m_ActiveDevices.end(); ++itr)
	{

		tempDev = itr->second;

		// If the device is connected
		if (tempDev->IsConnected())
		{

			tempDev->Update(deltaTime);

		}
		else {

			// act on disconnection
			
		}

	}

}

bool InputManager::Initialize() noexcept
{
#if defined(BLADE_BUILD_D3D)

	// XInput is already initialized
	BLADE_TRACE("InputManager (XInput) Initialized successfully");

#elif defined(BLADE_BUILD_PS4)

	// init PS4 pad library
	if (scePadInit() != SCE_OK) {

		std::cerr << "PS4 Pad library failed to initialize" << std::endl;
		
		return false;

	}

#endif

	return true;
}


int InputManager::EnumerateDevices() noexcept
{

	int dDevCount{ 0 };

#if defined(BLADE_BUILD_D3D)
	
	XINPUT_STATE xiState{ 0 };

	for (int i = 0; i < XUSER_MAX_COUNT; ++i)
	{

		ZeroMemory(&xiState, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &xiState) == ERROR_SUCCESS)
		{

			// Device shows as connected
			++dDevCount;

			// Check the device doesn't already exist in the pool or active device list
			if (!PooledDeviceExists(i) && !ActiveDeviceExists(i))
			{

				XInputDevice* xDev = new XInputDevice(i, DeviceType::Joypad);

				// Add the new device to the pool

				m_DevicePool.push_back(xDev);

			}

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
	for (unsigned int i = 0; (i < m_DevicePool.size()); ++i) {

		tmpDev = m_DevicePool[i];

		if (tmpDev->GetDeviceID() == deviceId) {

			return tmpDev->GetDeviceType();

		}

	}

	// Not found
	return DeviceType::DEVTYPE_ERROR;
}

bool Blade::InputManager::PooledDeviceExists(int deviceId)
{

	std::vector<InputDevice*>::iterator itr{ m_DevicePool.begin() };

	InputDevice* tempDev{ nullptr };

	for (itr = m_DevicePool.begin(); itr != m_DevicePool.end(); ++itr)
	{

		tempDev = *itr;

		if (tempDev->GetDeviceID() == deviceId)
		{

			return true;

		}

	}

	return false;
}

bool Blade::InputManager::ActiveDeviceExists(int deviceId)
{
	std::map<Player, InputDevice*>::iterator itr = m_ActiveDevices.begin();

	InputDevice* tempDev{ nullptr };

	for (itr = m_ActiveDevices.begin(); itr != m_ActiveDevices.end(); ++itr)
	{

		tempDev = itr->second;

		if (tempDev->GetDeviceID() == deviceId)
		{

			return true;

		}

	}

	return false;
}


bool Blade::InputManager::AssignDeviceToPlayer(Player playerID, int deviceNumber)
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

bool Blade::InputManager::UnassignDevice(Player playerID)
{

	// Find device
	std::map<Player, InputDevice*>::iterator itr = m_ActiveDevices.find(playerID);

	// Fail if not found
	if (itr == m_ActiveDevices.end())
	{

		return false;

	}

	// Remove from the active devices map
	InputDevice* tempDev = itr->second;

	m_ActiveDevices.erase(itr);

	// If the device is still connected, add it to the device pool
	if (tempDev->IsConnected())
	{

		m_DevicePool.push_back(tempDev);

	}
	else {

		// Otherwise, delete the device, it is not connected
		delete tempDev;

	}

	return false;
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
