#ifndef THREADING_UTILS_H_
#define THREADING_UTILS_H_

#include "trace.h"

#if defined(BLADE_BUILD_D3D)
#include <windows.h>
#endif


namespace Blade
{
	enum CpuCoreNumber
	{
		CPU_0 = 1,
		CPU_1 = 2,
		CPU_2 = 4,
		CPU_3 = 8,
		CPU_4 = 16,
		CPU_5 = 32,
		CPU_6 = 64,
		CPU_7 = 128
	};

	bool AttachCurrentThreadToCore(unsigned int coreNumber)
	{
	#if defined(BLADE_BUILD_D3D)
		auto handle = GetCurrentThread();
		if (!SetThreadAffinityMask(handle, coreNumber))
		{
			BLADE_ERROR("Failed to attach current thread to core: "
				+ std::to_string(coreNumber)
				+ ". Error code: " + std::to_string(GetLastError()));
			return false;
		}

		return true;
	#endif
	};
}

#endif //THREADING_UTILS_H_
