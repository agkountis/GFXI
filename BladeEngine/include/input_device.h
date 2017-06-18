#ifndef BLADE_INPUT_DEVICE_H_
#define BLADE_INPUT_DEVICE_H_

#include "input_state.h"

#if defined(BLADE_BUILD_D3D)

#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#include <utility>

#include "GLM/glm.hpp"

// required library files
#pragma comment (lib, "Xinput.lib")
#pragma comment (lib, "Xinput9_1_0.lib")

#elif defined (BLADE_BUILD_PS4)

#include <pad.h>

#endif

/*
\brief The delta tolerance between states of an analog sensor before a change is recognized. Normalized to [0.0...1.0]
*/

#if defined(BLADE_BUILD_D3D)

#define DEADZONE_ASTICK_L	XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
#define DEADZONE_ASTICK_R	XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
#define DEADZONE_ATRIGGERS	XINPUT_GAMEPAD_TRIGGER_THRESHOLD
#define VIBRATION_THRESHOLD	65535

#define THUMBSTICK_LIMIT_X_MIN	-32767
#define THUMBSTICK_LIMIT_X_MAX	32767
#define THUMBSTICK_LIMIT_Y_MIN	-32767
#define THUMBSTICK_LIMIT_Y_MAX	32767

#define AXIS_SHIFT 0

#elif defined(BLADE_BUILD_PS4)

/*
Updates to PS4 firmware means these values are best not to be predefined, but defined
by data from a call to scePadGetControllerInformation (returning a pad structure). These
values are for leagacy use only.
*/
#define DEADZONE_ASTICK_L	0x0d
#define DEADZONE_ASTICK_R	0x0d
#define DEADZONE_ATRIGGERS	0x0d
#define VIBRATION_THRESHOLD	255

#define THUMBSTICK_LIMIT_X_MIN	0
#define THUMBSTICK_LIMIT_X_MAX	255
#define THUMBSTICK_LIMIT_Y_MIN	0
#define THUMBSTICK_LIMIT_Y_MAX	255

#define AXIS_SHIFT -128

#else

// ignore values?
#define DEADZONE_ASTICK_L	0x00
#define DEADZONE_ASTICK_R	0x00
#define DEADZONE_ATRIGGERS	0x00

#define THUMBSTICK_LIMIT_X_MIN	0
#define THUMBSTICK_LIMIT_X_MAX	0
#define THUMBSTICK_LIMIT_Y_MIN	0
#define THUMBSTICK_LIMIT_Y_MAX	0

#define AXIS_SHIFT 0

#endif

namespace Blade
{
	/*
	* \brief Describe the type of the device.
	*/
	enum class DeviceType
	{
		KEYBAORD,
		JOYPAD,
		OTHER,
		DEVTYPE_ERROR
	};

	/*
	\brief Describe the analog dead zones. 
	*/
	enum class AnalogDeadzone
	{
		ANALOG_STICK_LEFT,
		ANALOG_STICK_RIGHT,
		ANALOG_TRIGGER
	};

	/*
	\brief InputDevice provides a useful abstraction for every type of input device.
	*/
	class InputDevice
	{
	private:
		/*
		\brief The ID of the device.
		*/
		int m_deviceID{ -1 };

		/*
		 * \brief The most recent recorded state of the device
		 */
		InputState m_CurrentState;

		/*
		 * \brief The state of the device one polling event before the current recorded state
		 */
		InputState m_PreviousState;

		/*
		 * \brief Deadzone value for left analog stick
		 */
		float m_DeadZoneLeftStick{ DEADZONE_ASTICK_L };

		/*
		 * \brief Deadzone value for left analog stick
		 */
		float m_DeadZoneRightStick{ DEADZONE_ASTICK_R };

		/*
		 * \brief Deadzone value for analog triggers
		 */
		float m_DeadZoneTriggers{ DEADZONE_ATRIGGERS };

		/*
		 * \brief Enumeration of device type
		 */
		DeviceType m_DeviceType{ DeviceType::DEVTYPE_ERROR };

	protected:

		/*
		 * \brief Filters input state data
		 * \param stateIn The initial input state that need to be filtered
		 * \param stateOut The reference to the final state after the filtering process.
		 * \details Applies limits, scales and clamps for the device (such as deadzones and tolerances) to the specified input data
		 */
		static void FilterStateData(const InputState& stateIn, InputState& stateOut);

		/*
		 * \brief Gets the device ID (input API handle)
		 * \param id The ID to set.
		 */
		void SetDeviceID(int id) { m_deviceID = id; }

		/*
		 * \brief Sets the type of the device
		 * \param devType The type of the device.
		 * \brief param devType The type of the device
		 */
		void SetDeviceType(DeviceType devType) { m_DeviceType = devType; }

		/*
		 * \brief Moves the newest input state to the previous state and stores the provided state as newest
		 * \param state The input state.
		 */
		void SetInputState(const InputState& state);

		/*
		 * \brief Initialize the selected InputDevice
		 * \details Allocates any needed resources and handles to use the device, and prepares it to a ready state
		 * \remarks Any pre-initialization and resource allocation to be able to immediately use the device is performed here
		 * \return True if successful, false otherwise
		 */
		virtual bool Initialize() = 0;

	public:
		/*
		\brief The constructor of the InputDevice.
		*/
		InputDevice();

		virtual ~InputDevice() = default;

		InputDevice(const InputDevice&) = delete;

		InputDevice& operator=(const InputDevice& rhs) = delete;

		InputDevice(InputDevice&& src) = delete;

		InputDevice& operator=(InputDevice&& rhs) = delete;

		/*
		 * \brief  Constructors and destructor of the InputDevice.
		 * Copy/Move operator and assignments are deleted.
		 */
		InputDevice(int device_id, DeviceType devType);

		/*
		\brief Get the current input state.
		\return The current input state of the device.
		*/
		const InputState& GetInputState() const { return GetCurrentState(); }

		/*
		 * \brief Gets the device ID (input API handle)
		 * \return The ID of the device
		 */
		int GetDeviceID() const { return m_deviceID; }

		/*
		 * \brief Updates the active devices to the latest input states available and buffers the most recent previous state
		 * \param fDeltaTime the delta time.
		 */
		virtual void Update(float fDeltaTime) = 0;

		/*
		 * \brief Sets vibration parameters of input device (if supported)
		 * \param leftMotor The amount of left motor of the controller
		 * \param rightMotor The amount of right motor of the controller.
		 * \details Left and right motors are set independently from 0.0 (off) to 1.0 (100%)
		 * \return True if successful, false otherwise
		 */
		virtual bool SetVibration(float leftMotor, float rightMotor) const = 0;

		/*
		 * \brief Set dead zone information for an analog sensor on the the device (stick, trigger, etc)
		 * \details Overrides the pre-defined DEADZONE_ASTICKL/DEADZONE_ASTICKR/DEADZONE_ATRIGGERS values
		 * \param flag The identifier of the dead zone that you want to affect.
		 * \param value The analog dead zone threshold.
		 * \remarks The flag enum is of type Analog_Deadzone, and represents which value to update.
		 * Use AnalogStickL to set the left analog stick dead zone, AnalogStickR to set the right
		 * analog stick dead zone,	and AnalogTrigger to set the dead zone for both analog triggers.
		 * \remarks Individual trigger dead zone values are not supported
		 */
		void SetDeadzone(AnalogDeadzone flag, float value);

		/*
		 * \brief Get dead zone information for an analog sensor on the the device (stick, trigger, etc)
		 * \param flag The flag of the dead zone.
		 * \remarks The flag enum is of type Analog_Deadzone, and represents which value to update.
		 * Use AnalogStickL to get the left analog stick dead zone, AnalogStickR to get the right
		 * analog stick dead zone,	and AnalogTrigger to get the dead zone for both analog triggers.
		 * \remarks Individual trigger dead zone values are not supported
		 */
		float GetDeadzone(AnalogDeadzone flag) const;

		/*
		 * \brief Checks device is connected
		 * \return True if the device is connected and functioning, false otherwise
		 */
		virtual bool IsConnected() const = 0;

		/*
		 * \brief Get the type of device
		 * \return Enum of DeviceType of the device if successful, DeviceType enum DEVTYPE_ERROR otherwise
		 */
		DeviceType GetDeviceType() const { return m_DeviceType; }

		/*
		 * \brief Gets the last (newest) buffered input state to read
		 * \return The current input state. 
		 */
		const InputState& GetCurrentState() const { return m_CurrentState; }

		/*
		 * \brief Gets the previous buffered previous input state to read
		 * \return The previous input state.
		 */
		const InputState& GetPreviousState() const { return m_PreviousState; }
	};
}

#endif
