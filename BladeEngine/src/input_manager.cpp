#include "input_manager.h"
#include "math_utils.h"

using namespace Blade;

namespace Blade
{
	InputManager::~InputManager()
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

	void InputManager::SetMouseButtonState(MouseButton button, bool value)
	{
		m_MouseButton[static_cast<int>(button)] = value;
	}

	bool InputManager::QueryMouseButtonState(MouseButton button)
	{
		return m_MouseButton[static_cast<int>(button)];
	}

	void InputManager::UpdateMousePos(Vec2i mousepos)
	{
		m_MousePosPrevious = m_MousePos;
		m_MousePos = mousepos;

		m_MouseMovement = m_MousePos - m_MousePosPrevious;
	}

	Vec2f InputManager::GetAnalogStickVector(JoypadNumber player, InputSensor sensor)
	{
		InputDevice* dev = GetActiveDevice(player);

		if (dev == nullptr)
		{
			// return a zero vector (equivalent to no input)
			return Vec2f(0.0f, 0.0f);
		}

		InputState inState = dev->GetInputState();

		if (sensor == STICK_LEFT)
		{
			return Vec2f(inState.stickLeft.axisX, inState.stickLeft.axisY);
		}

		if (sensor == STICK_RIGHT)
		{
			return Vec2f(inState.stickRight.axisX, inState.stickRight.axisY);
		}

		// Catch-All
		return Vec2f(0.0f, 0.0f);
	}

	bool InputManager::QueryKeyState(VirtualKey key) const noexcept
	{
		return KeyboardInput::QueryKeyState(key);
	}

	bool InputManager::QueryAllKeyStates(std::map<VirtualKey, bool>& destMap) const noexcept
	{
		return KeyboardInput::QueryAllKeyStates(destMap);
	}

	Vec2f InputManager::QueryMouseMovement()
	{
		Vec2f movement{ m_MouseMovement };

		m_MouseMovement = Vec2f{ 0.0f, 0.0f };

		return movement;
	}

	Vec2f InputManager::QueryMouseMovementNormalized()
	{
		Vec2f movement = QueryMouseMovement();

		if (MathUtils::Lengthf(movement) > 0.0f)
		{
			return MathUtils::Normalize(movement);
		}

		return movement;
	}

	Vec2i InputManager::QueryMousePosition() const noexcept
	{
		return m_MousePos;
	}

	//bool InputManager::QueryMouseButtonState(MouseButton button)
	//{
	//
	//	if (button == MouseButton::LEFT)
	//	{
	//		return ((::GetKeyState(VK_LBUTTON) & 0x80) != 0);
	//	}
	//	else if (button == MouseButton::RIGHT)
	//	{
	//		return ((::GetKeyState(VK_RBUTTON) & 0x80) != 0);
	//	}
	//
	//	return false;
	//}

	bool InputManager::QueryDeviceState(JoypadNumber player, InputSensor btn)
	{
		InputDevice* dev = GetActiveDevice(player);

		if (dev)
		{
			switch (btn)
			{
			case STICK_LEFT:
				// left stick
				return dev->GetInputState().stickLeft.axisX != 0.0f || dev->GetInputState().stickLeft.axisY != 0.0f;
			case STICK_RIGHT:
				// right stick
				return dev->GetInputState().stickRight.axisX != 0.0f || dev->GetInputState().stickRight.axisY != 0.0f;
			case TRIGGER_LEFT:
				// left trigger
				return dev->GetInputState().triggerLeft != 0.0f;
			case TRIGGER_RIGHT:
				// right trigger
				return dev->GetInputState().triggerRight != 0.0f;
			default:
				// Digital button bit mask
				return (dev->GetInputState().digitalButtonData & btn) != 0;
			}
		}

		return false;
	}

	bool InputManager::QueryDeviceAllStates(JoypadNumber player, std::map<InputSensor, bool>& stateMap)
	{
		InputDevice* dev = GetActiveDevice(player);

		if (dev == nullptr)
		{
			return false;
		}

		InputState inState = dev->GetInputState();

		// Digital sensors to iterate
		InputSensor digitalSensors[]{
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

		for (auto sensor : digitalSensors)
		{
			// check bit flag
			stateMap[sensor] = (inState.digitalButtonData & sensor) != 0;
		}

		// Analog Sticks
		stateMap[STICK_LEFT] = inState.stickLeft.axisX != 0.0f || inState.stickLeft.axisY != 0.0f;
		stateMap[STICK_RIGHT] = inState.stickRight.axisX != 0.0f || inState.stickRight.axisY != 0.0f;

		// Analog Triggers
		stateMap[TRIGGER_LEFT] = inState.triggerLeft > 0.0f;
		stateMap[TRIGGER_RIGHT] = inState.triggerRight > 0.0f;

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
					XInputDevice* xDev{ new XInputDevice(i, DeviceType::JOYPAD) };

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
		switch (active_number)
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

	DeviceType InputManager::DevicePoolQueryType(int deviceId)
	{
		InputDevice* tmpDev{ nullptr };

		// Search for device_id
		for (unsigned int i = 0; (i < m_DevicePool.size()); ++i)
		{
			tmpDev = m_DevicePool[i];

			if (tmpDev->GetDeviceID() == deviceId)
			{
				return tmpDev->GetDeviceType();
			}
		}

		// Not found
		return DeviceType::DEVTYPE_ERROR;
	}

	bool InputManager::PooledDeviceExists(int deviceId)
	{
		for (auto inputDevice : m_DevicePool)
		{
			if (inputDevice->GetDeviceID() == deviceId)
			{
				return true;
			}
		}

		return false;
	}

	bool InputManager::ActiveDeviceExists(int deviceId)
	{
		for (auto& entry : m_ActiveDevices)
		{
			if (entry.second->GetDeviceID() == deviceId)
			{
				return true;
			}
		}

		return false;
	}


	bool InputManager::AssignDeviceToPlayer(JoypadNumber playerID, int deviceNumber)
	{
		// Exceeded bounds
		if (deviceNumber > m_DevicePool.size() || deviceNumber < 0 || m_DevicePool.size() == 0)
		{
			return false;
		}

		// Add device to active device map
		m_ActiveDevices[playerID] = m_DevicePool[deviceNumber];

		// Remove from device pool - this device is now in use
		auto itr = m_DevicePool.begin();

		std::advance(itr, deviceNumber);

		m_DevicePool.erase(itr);

		return true;
	}

	bool InputManager::UnassignDevice(JoypadNumber playerID)
	{
		// Find device
		auto itr = m_ActiveDevices.find(playerID);

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
		else
		{
			// Otherwise, delete the device, it is not connected
			delete tempDev;
		}

		return false;
	}

	InputDevice* InputManager::GetActiveDevice(JoypadNumber playerID)
	{
		// Find by iterator
		auto itr = m_ActiveDevices.find(playerID);

		// return result or nullptr
		if (itr != m_ActiveDevices.end())
		{
			return itr->second;
		}

		return nullptr;
	}
}
