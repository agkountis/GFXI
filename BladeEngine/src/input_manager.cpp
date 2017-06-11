#include "input_manager.h"
using namespace Blade;

Vec2f InputManager::GetAnalogStickVector(JoypadNumber player, Input_Sensor sensor)
{

	InputDevice* dev = GetActiveDevice(player);

	if (dev == nullptr) {

		// return a zero vector (equivalent to no input)
		return Vec2f(0.0f, 0.0f);

	}

	InputState inState = dev->GetInputState();
	
	if (sensor == STICK_LEFT)
	{
		return Vec2f(inState.stickLeft.axisX, inState.stickLeft.axisY);
	}
	else if (sensor == STICK_RIGHT)
	{
		return Vec2f(inState.stickRight.axisX, inState.stickRight.axisY);
	}

	// Catch-All
	return Vec2f(0.0f, 0.0f);
}

bool InputManager::QueryDeviceState(JoypadNumber player, Input_Sensor btn)
{

	InputDevice* dev = GetActiveDevice(player);

	if (dev == nullptr) {

		return false;

	}

	// if the caller is requesting one of the analog sticks
	if (btn == Input_Sensor::STICK_LEFT)
	{
		// left stick
		return (dev->GetInputState().stickLeft.axisX != 0.0f || dev->GetInputState().stickLeft.axisY != 0.0f);
	} 
	else if (btn == Input_Sensor::STICK_RIGHT)
	{
		// right stick
		return (dev->GetInputState().stickRight.axisX != 0.0f || dev->GetInputState().stickRight.axisY != 0.0f);
	}
	else if (btn == Input_Sensor::TRIGGER_LEFT)
	{
		// left trigger
		return (dev->GetInputState().triggerLeft != 0.0f);
	}
	else if (btn == Input_Sensor::TRIGGER_RIGHT)
	{
		// right trigger
		return (dev->GetInputState().triggerRight != 0.0f);
	}
	else
	{
		// Digital button bit mask
		return ((dev->GetInputState().digitalButtonData & btn) != 0);
	}

	// catch-all
	return false;
}

bool InputManager::QueryDeviceAllStates(JoypadNumber player, std::map<Input_Sensor, bool>& stateMap)
{

	InputDevice* dev = GetActiveDevice(player);

	if (dev == nullptr) {

		return false;

	}

	InputState inState = dev->GetInputState();

	// Digital sensors to iterate
	Input_Sensor digitalSensors[]{
		BTN_FACE_1,
		BTN_FACE_2,
		BTN_FACE_3,
		BTN_FACE_4,
		BTN_OPTION_1,
		BTN_OPTION_2,
		BTN_SHOULDER_L,
		BTN_SHOULDER_R,
		BTN_STICK_L,
		BTN_STICK_R,
		DPAD_UP,
		DPAD_DOWN,
		DPAD_LEFT,
		DPAD_RIGHT
	};

	for (auto sensor : digitalSensors) {
		// check bit flag
		stateMap[sensor] = ((inState.digitalButtonData & sensor) != 0);
	}

	// Analog Sticks
	stateMap[STICK_LEFT] = (inState.stickLeft.axisX != 0.0f || inState.stickLeft.axisY != 0.0f);
	stateMap[STICK_RIGHT] = (inState.stickRight.axisX != 0.0f || inState.stickRight.axisY != 0.0f);

	// Analog Triggers
	stateMap[TRIGGER_LEFT] = (inState.triggerLeft > 0.0f);
	stateMap[TRIGGER_RIGHT] = (inState.triggerRight > 0.0f);


	return true;
}

void InputManager::Update(float deltaTime)
{

	// re-enumerate input API for any newly connected devices since the last check
	//int result = EnumerateDevices();

	


	// Update the state of active input devices (in the active map, with player assignments)
	for (auto& entry : m_ActiveDevices) 
	{
		InputDevice* tempDev{ entry.second };

		// If the device is connected
		if (tempDev->IsConnected())
		{

			tempDev->Update(deltaTime);

		}
		else 
		{

			// Unassign the device from player, and delete if disconnected
			UnassignDevice(entry.first);
			return;
		}
	}

	// Check the device pool for device removals (connected=false)
	auto it = m_DevicePool.begin();

	while (it != m_DevicePool.end())
	{
		InputDevice* tempDev{ *it };

		if (!tempDev->IsConnected())
		{

			it = m_DevicePool.erase(it);

			delete tempDev;

		}
		else
		{
			++it;
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

	// Enumerate the devices
	EnumerateDevices();

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
				BLADE_TRACE("Adding new device to device pool");
				m_DevicePool.push_back(xDev);
				UpdateActiveDevices();		
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


void InputManager::UpdateActiveDevices()
{
	auto active_number{ m_ActiveDevices.size() };
	switch ( active_number)
	{
	case 0:
		AssignDeviceToPlayer(JoypadNumber::JOYPAD1, 0);
		break;
	case 1:
		AssignDeviceToPlayer(JoypadNumber::JOYPAD2, 0);
		break;

	case 2:
		AssignDeviceToPlayer(JoypadNumber::JOYPAD3, 0);
		break;

	case 3:
		AssignDeviceToPlayer(JoypadNumber::JOYPAD4, 0);
		break;
	}

		

		

		
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
	std::map<JoypadNumber, InputDevice*>::iterator itr = m_ActiveDevices.begin();

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


bool Blade::InputManager::AssignDeviceToPlayer(JoypadNumber playerID, int deviceNumber)
{

	// Exceeded bounds
	if (deviceNumber > m_DevicePool.size() || deviceNumber < 0 || m_DevicePool.size()==0)
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

bool Blade::InputManager::UnassignDevice(JoypadNumber playerID)
{

	// Find device
	std::map<JoypadNumber, InputDevice*>::iterator itr = m_ActiveDevices.find(playerID);

	// Fail if not found
	if (itr == m_ActiveDevices.end())
	{

		return false;

	}

	// Remove from the active devices map
	InputDevice* tempDev = itr->second;

	BLADE_TRACE("Removing input device from active device map");
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

InputDevice * InputManager::GetActiveDevice(JoypadNumber playerID)
{

	// Find by iterator
	std::map<JoypadNumber, InputDevice*>::iterator itr = m_ActiveDevices.find(playerID);

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
	for (auto& entry : m_ActiveDevices)
	{
		delete entry.second;
	}

	m_ActiveDevices.clear();

	// invalidate and release inactive devices in the device pool
	for (auto inputDevice : m_DevicePool)
	{
		delete inputDevice;
	}

	m_DevicePool.clear();
}
