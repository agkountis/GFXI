#ifndef BLADE_GAPI_CONTEXT_H_
#define BLADE_GAPI_CONTEXT_H_

#include <Windows.h>

namespace Blade
{
	/*
	\brief Graphic Api Context class of the engine
	*/
	class GAPIContext
	{
	public:
		GAPIContext() = default;

		virtual ~GAPIContext() = default;

		virtual bool Create(LUID* luid) = 0;
	};
}

#endif //BLADE_GAPI_CONTEXT_H_
