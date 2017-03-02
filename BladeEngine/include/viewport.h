#ifndef BLADE_VIEWPORT_H_
#define BLADE_VIEWPORT_H_
#include "d3d/D3D11_viewport.h"

namespace Blade
{
#if defined(BLADE_BUILD_D3D)
	/**
	 * \brief Type alias of a concrete Viewport implementation 
	 * depending on the build configuration.
	 */
	using Viewport = D3D11Viewport;
#else
#endif
}

#endif //BLADE_VIEWPORT_H_
