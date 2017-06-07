#ifndef BLADE_GAPI_CONTEXT_H_
#define BLADE_GAPI_CONTEXT_H_

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

		virtual bool Create() = 0;
	};
}

#endif //BLADE_GAPI_CONTEXT_H_
