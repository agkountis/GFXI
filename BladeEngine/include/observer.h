#ifndef BLADE_OBSERVER_H_
#define BLADE_OBSERVER_H_
#include "types.h"
#include <string>

namespace Blade
{
	/*
	\brief Observer class of the engine.
	\details The engine provides observer pattern interface
	*/
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer();

		virtual void OnMessage(const MessageContainer<std::string>& msg) = 0;
	};
}

#endif //BLADE_OBSERVER_H_
