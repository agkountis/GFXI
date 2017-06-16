#ifndef BLADE_RESOURCE_UTILS_H_
#define BLADE_RESOURCE_UTILS_H_
#include "sample.h"
#include "d3d/D3D11_texture.h"
#include "emitter_component.h"

namespace Blade
{
	namespace ResourceUtils
	{
		AudioSample* GetAudioSample(const std::wstring& fname) noexcept;

#ifdef WIN32
		D3D11Texture* GetD3D11Texture(const std::wstring& fname) noexcept;
#endif

		EmitterDescriptor* GetEmitterDescriptor(const std::wstring& fname) noexcept;
	}
}

#endif
