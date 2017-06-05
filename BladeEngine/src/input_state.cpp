#include "input_state.h"

using namespace Blade;

InputState::InputState() : digitalButtonData(0), triggerLeft(0.0f), triggerRight(0.0f), stickLeft({ 0.0f, 0.0f }), stickRight({ 0.0f, 0.0f })
{
}

#if defined(BLADE_BUILD_D3D)

InputState::InputState(XINPUT_STATE & state)
{
	// copy analog triggers (normalize to [0..1]
	triggerLeft = static_cast<float>(state.Gamepad.bLeftTrigger / TRIGGER_THRESHOLD);
	triggerRight = static_cast<float>(state.Gamepad.bRightTrigger / TRIGGER_THRESHOLD);

	// copy left thumbstick (normalize to [0..1]
	stickLeft.axisX = static_cast<float>(state.Gamepad.sThumbLX / STICK_THRESHOLD);
	stickLeft.axisY = static_cast<float>(state.Gamepad.sThumbLY / STICK_THRESHOLD);

	// copy right thumbstick (normalize to [0..1]
	stickRight.axisX = static_cast<float>(state.Gamepad.sThumbRX / STICK_THRESHOLD);
	stickRight.axisY = static_cast<float>(state.Gamepad.sThumbRY / STICK_THRESHOLD);

	// read buttons and set values
	WORD buttonData = state.Gamepad.wButtons;

	// Check Dstate for directional pad (d-pad)
	if (buttonData & XINPUT_GAMEPAD_DPAD_UP) {
		digitalButtonData &= JOYDPAD_UP;
	}

	if (buttonData & XINPUT_GAMEPAD_DPAD_DOWN) {
		digitalButtonData &= JOYDPAD_DOWN;
	}

	if (buttonData & XINPUT_GAMEPAD_DPAD_LEFT) {
		digitalButtonData &= JOYDPAD_LEFT;
	}

	if (buttonData & XINPUT_GAMEPAD_DPAD_RIGHT) {
		digitalButtonData &= JOYDPAD_RIGHT;
	}

	// Check for face buttons
	if (buttonData & XINPUT_GAMEPAD_A) {
		digitalButtonData &= JOYBTN_FACE1;
	}

	if (buttonData & XINPUT_GAMEPAD_B) {
		digitalButtonData &= JOYBTN_FACE2;
	}

	if (buttonData & XINPUT_GAMEPAD_X) {
		digitalButtonData &= JOYBTN_FACE3;
	}

	if (buttonData & XINPUT_GAMEPAD_Y) {
		digitalButtonData &= JOYBTN_FACE4;
	}

	// check for option buttons
	if (buttonData & XINPUT_GAMEPAD_START) {
		digitalButtonData &= JOYBTN_OPTION1;
	}

	if (buttonData & XINPUT_GAMEPAD_BACK) {
		digitalButtonData &= JOYBTN_OPTION2;
	}

	// check for shoulder buttons ("bumper" or "L1/L2)
	if (buttonData & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		digitalButtonData &= JOYBTN_SHOULDER1;
	}

	if (buttonData & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		digitalButtonData &= JOYBTN_SHOULDER2;
	}

}

#elif defined(BLADE_BUILD_PS4)

// constructor with PS4 types here

#else

// constructor with other types here

#endif

InputState::~InputState()
{
}
