#ifndef BLADE_WINDOWING_TYPES_H_
#define BLADE_WINDOWING_TYPES_H_

namespace Blade
{
	using ReshapeFunc = void(*)(int, int);
	using KeyboardFunc = void(*)(unsigned char, int, int);
	using KeyboardUpFunc = void(*)(unsigned char, int, int);
	using SpecialFunc = void(*)(int, int, int);
	using SpecialUpFunc = void(*)(int, int, int);
	using MouseFunc = void(*)(int, bool, int, int);
	using MotionFunc = void(*)(int, int);
	using PassiveMotionFunc = void(*)(int, int);

	struct WindowFunctionCallbacks
	{
		ReshapeFunc reshape_func{ nullptr };
		KeyboardFunc keyboard_func{ nullptr };
		KeyboardUpFunc keyboard_up_func{ nullptr };
		SpecialFunc special_func{ nullptr };
		SpecialUpFunc special_up_func{ nullptr };
		MouseFunc mouse_func{ nullptr };
		MotionFunc motion_func{ nullptr };
		PassiveMotionFunc passive_motion_func{ nullptr };
	};
}

#endif //BLADE_WINDOWING_TYPES_H_
