#include "input_manager.h"

using namespace Blade;


bool InputManager::Initialize() noexcept
{
	return true;
}

const int InputManager::EnumerateDevices() noexcept
{
#if defined(BLADE_BUILD_D3D)
	//PC code here
	return 1;
#else
	//PS4 code here
	return 1;
#endif
}
