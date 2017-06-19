#ifndef BLADE_VIRTUAL_KEYS_H_
#define BLADE_VIRTUAL_KEYS_H_

#include <Windows.h>

namespace Blade
{
	/**
	\brief Keyboard key identifier.
	*/
	enum VirtualKey : int
	{
		KEY_BACKSPACE = VK_BACK,
		KEY_TAB = VK_TAB,
		KEY_RETURN = VK_RETURN,
		KEY_PAUSE = VK_PAUSE,
		KEY_ESC = VK_ESCAPE,
		KEY_SPACE = VK_SPACE,
		KEY_PGUP = VK_PRIOR,
		KEY_PGDN = VK_NEXT,
		KEY_END = VK_END,
		KEY_HOME = VK_HOME,
		KEY_LEFT = VK_LEFT,
		KEY_RIGHT = VK_RIGHT,
		KEY_UP = VK_UP,
		KEY_DOWN = VK_DOWN,
		KEY_SELECT = VK_SELECT,
		KEY_PRINT = VK_PRINT,
		KEY_PRTSCRN = VK_SNAPSHOT,
		KEY_INSERT = VK_INSERT,
		KEY_DELETE = VK_DELETE,
		KEY_HELP = VK_HELP,

		// number (non numeric keypad)
		KEY_0 = 0x30,
		KEY_1 = 0x31,
		KEY_2 = 0x32,
		KEY_3 = 0x33,
		KEY_4 = 0x34,
		KEY_5 = 0x35,
		KEY_6 = 0x36,
		KEY_7 = 0x37,
		KEY_8 = 0x38,
		KEY_9 = 0x39,

		// letters & glyphs
		KEY_A = 0x41,
		KEY_B = 0x42,
		KEY_C = 0x43,
		KEY_D = 0x44,
		KEY_E = 0x45,
		KEY_F = 0x46,
		KEY_G = 0x47,
		KEY_H = 0x48,
		KEY_I = 0x49,
		KEY_J = 0x4A,
		KEY_K = 0x4B,
		KEY_L = 0x4C,
		KEY_M = 0x4D,
		KEY_N = 0x4E,
		KEY_O = 0x4F,
		KEY_P = 0x50,
		KEY_Q = 0x51,
		KEY_R = 0x52,
		KEY_S = 0x53,
		KEY_T = 0x54,
		KEY_U = 0x55,
		KEY_V = 0x56,
		KEY_W = 0x57,
		KEY_X = 0x58,
		KEY_Y = 0x59,
		KEY_Z = 0x5A,

		// Number pad
		KEY_NUM_0 = VK_NUMPAD0,
		KEY_NUM_1 = VK_NUMPAD0,
		KEY_NUM_2 = VK_NUMPAD0,
		KEY_NUM_3 = VK_NUMPAD0,
		KEY_NUM_4 = VK_NUMPAD0,
		KEY_NUM_5 = VK_NUMPAD0,
		KEY_NUM_6 = VK_NUMPAD0,
		KEY_NUM_7 = VK_NUMPAD0,
		KEY_NUM_8 = VK_NUMPAD0,
		KEY_NUM_9 = VK_NUMPAD0,

		// Number pad symbols
		KEY_NUM_MULTIPLY = VK_MULTIPLY,
		KEY_NUM_ADD = VK_ADD,
		KEY_NUM_SUBTRACT = VK_SUBTRACT,
		KEY_NUM_DECIMAL = VK_DECIMAL,
		KEY_NUM_DIVIDIE = VK_DIVIDE,

		// Function keys
		KEY_F1 = VK_F1,
		KEY_F2 = VK_F2,
		KEY_F3 = VK_F3,
		KEY_F4 = VK_F4,
		KEY_F5 = VK_F5,
		KEY_F6 = VK_F6,
		KEY_F7 = VK_F7,
		KEY_F8 = VK_F8,
		KEY_F9 = VK_F9,
		KEY_F10 = VK_F10,
		KEY_F11 = VK_F11,
		KEY_F12 = VK_F12,
		KEY_F13 = VK_F13,
		KEY_F14 = VK_F14,
		KEY_F15 = VK_F15,
		KEY_F16 = VK_F16,
		KEY_F17 = VK_F17,
		KEY_F18 = VK_F18,
		KEY_F19 = VK_F19,
		KEY_F20 = VK_F20,
		KEY_F21 = VK_F21,
		KEY_F22 = VK_F22,
		KEY_F23 = VK_F23,
		KEY_F24 = VK_F24,

		// Shift and control
		KEY_LSHIFT = VK_LSHIFT,
		KEY_RSHIFT = VK_RSHIFT,
		KEY_LCTRL = VK_LCONTROL,
		KEY_RCTRL = VK_RCONTROL,

		// Misc
		KEY_LMENU = VK_LMENU,
		KEY_RMENU = VK_RMENU,
		KEY_NUM_SEPR = VK_SEPARATOR,
		KEY_WIN_L = VK_LWIN,
		KEY_WIN_R = VK_RWIN,
		KEY_APPS = VK_APPS
	};
};

#endif
