#ifndef BLADE_INPUT_STATE_H_
#define BLADE_INPUT_STATE_H_

//If we are building for d3d -> pc version
#if defined(BLADE_BUILD_D3D)

#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#include <utility>

// required library files
#pragma comment (lib, "Xinput.lib")
#pragma comment (lib, "Xinput9_1_0.lib")

#elif defined (BLADE_BUILD_PS4)

#include <pad.h>

#endif

// Joypad digital face buttons (ABXY/Shapes)
#define JOYBTN_FACE1		0x0001
#define JOYBTN_FACE2		0x0002
#define JOYBTN_FACE3		0x0004
#define JOYBTN_FACE4		0x0008

// Joypad digital d-pad buttons (UDLR)
#define JOYDPAD_UP			0x0010
#define JOYDPAD_DOWN		0x0020
#define JOYDPAD_LEFT		0x0040
#define JOYDPAD_RIGHT		0x0080

// Joypad digital shoulder buttons (LBRB/L1R1)
#define JOYBTN_SHOULDER1	0x0100
#define JOYBTN_SHOULDER2	0x0200

// Joypad stick buttons (click down sticks)
#define JOYBTN_STICKL		0x0400
#define JOYBTN_STICKR		0x0800

// Option buttons (start etc)
#define JOYBTN_OPTION1		0x1000
#define JOYBTN_OPTION2		0x2000

// Thumbstick axis normalizing value (platform-based)
#if defined(BLADE_BUILD_D3D)

// Analog threshold normalizing values
#define STICK_THRESHOLD		32767	// xInput value [-32767..32767] per axis
#define TRIGGER_THRESHOLD	255		// xInput value [0..255]

#elif defined(BLADE_BUILD_PS4)

// Analog threshold normalizing values
#define STICK_THRESHOLD		255		// PS4 value [0..255]
#define TRIGGER_THRESHOLD	255		// PS4 value [0..255]

#endif

namespace Blade
{
	/*
	* \brief Enumeration for input device buttons (digital values)
	* \details Uses bit flags defined in the device to for mappings where available
	*/
	enum Input_Sensor {
		BTN_FACE_1 = JOYBTN_FACE1,
		BTN_FACE_2 = JOYBTN_FACE2,
		BTN_FACE_3 = JOYBTN_FACE3,
		BTN_FACE_4 = JOYBTN_FACE4,
		BTN_STICK_L = JOYBTN_STICKL,
		BTN_STICK_R = JOYBTN_STICKR,
		BTN_SHOULDER_L = JOYBTN_SHOULDER1,
		BTN_SHOULDER_R = JOYBTN_SHOULDER2,
		BTN_OPTION_1 = JOYBTN_OPTION1,
		BTN_OPTION_2 = JOYBTN_OPTION2,
		DPAD_UP = JOYDPAD_UP,
		DPAD_DOWN = JOYDPAD_DOWN,
		DPAD_LEFT = JOYDPAD_LEFT,
		DPAD_RIGHT = JOYDPAD_RIGHT,
		TRIGGER_LEFT,
		TRIGGER_RIGHT,
		STICK_LEFT,
		STICK_RIGHT,
	};

	/**
	* \brief Thumbstick structure to hold X/Y axis information
	* \details Uses STICK_THRESHOLD to normalize to floating point values in [0..1] range
	*/
	struct ThumbStick {
		float axisX;
		float axisY;
	};

	/**
	* \brief InputState describes the current state of a device.
	* \details Only joy pad support for the moment. A function to compare two states has to be provided
	*/
	struct InputState
	{
		InputState();

		// constructor to read state data according to platform
#if defined(BLADE_BUILD_D3D)

		InputState(XINPUT_STATE& state);

#elif defined (BLADE_BUILD_PS4)

		//InputState(PS4_DATA_TYPE_WHATEVER& state);

#else

		//InputState(OTHER_DATA TYPE& state);

#endif

		~InputState();

		InputState(const InputState& src) noexcept = default;
		InputState& operator=(const InputState& rhs)noexcept = default;
		InputState(InputState&& src) noexcept = default;
		InputState& operator=(InputState&& rhs) noexcept = default;

		int digitalButtonData{ 0 };
		ThumbStick stickLeft{ 0 };
		ThumbStick stickRight{ 0 };
		float triggerLeft{ 0.0f };
		float triggerRight{ 0.0f };
	
	};
	
}

#endif
