#ifndef BLADE_OCULUS_TEXTURE_H_
#define BLADE_OCULUS_TEXTURE_H_

#ifdef BLADE_BUILD_OVR

#ifdef BLADE_BUILD_D3D
#include "oculus_texture_d3d.h"

namespace Blade
{
	using OculusTexture = OculusTextureD3D;
}

#endif //BLADE_BUILD_D3D

#endif //BLADE_BUILD_OVR

#endif //BLADE_OCULUS_TEXTURE_H_
