#ifndef BLADE_SYSTEM_H_
#define BLADE_SYSTEM_H_
#include <vector>
#include "entity.h"

namespace Blade
{
	class System
	{
	public:
		System() = default;

		virtual ~System();

		virtual bool Initialize() noexcept = 0;

		virtual void Process(float deltaTime) noexcept = 0;
	};
}

#endif //BLADE_SYSTEM_H_
