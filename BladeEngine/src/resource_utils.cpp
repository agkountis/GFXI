#include "resource_utils.h"
#include "engine_context.h"

namespace Blade
{
	namespace ResourceUtils
	{
		AudioSample* GetAudioSample(const std::wstring& fname) noexcept
		{
			return G_ResourceManager.Get<AudioSample>(AUDIO_PATH + fname);
		}

		D3D11Texture* GetD3D11Texture(const std::wstring& fname) noexcept
		{
			return G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + fname);
		}

		EmitterDescriptor* GetEmitterDescriptor(const std::wstring& fname) noexcept
		{
			return G_ResourceManager.Get<EmitterDescriptor>(CONFIGURATION_PATH + fname);
		}
	}
}
