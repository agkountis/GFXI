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
#define STICK_THRESHOLD		32768	// xInput value [-32768..32768]
#define TRIGGER_THRESHOLD	255		// xInput value [0..255]

#elif defined(BLADE_BUILD_PS4)

// Analog threshold normalizing values
#define STICK_THRESHOLD		255		// PS4 value [0..255]
#define TRIGGER_THRESHOLD	255		// PS4 value [0..255]

#endif

namespace Blade
{

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
