#ifndef AUDIO_H_
#define AUDIO_H_
#include "types.h"

namespace Blade
{
	namespace Audio
	{
		bool InitAudio() noexcept;
		void DestroyAudio() noexcept;

		void SetAudioListener(const Mat4f& xform) noexcept;
	}
}

#endif  // AUDIO_H_
