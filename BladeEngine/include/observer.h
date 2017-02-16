#ifndef BLADE_OBSERVER_H_
#define BLADE_OBSERVER_H_
#include "types.h"

namespace Blade
{
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer();

		virtual void OnMessage(const MessageContainer& msg) = 0;
	};
}

#endif //BLADE_OBSERVER_H_
