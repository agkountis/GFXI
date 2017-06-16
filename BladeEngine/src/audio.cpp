#include <stdio.h>
#include "openal.h"
#include "audio.h"
#include "types.h"
#include "trace.h"

static ALCdevice* dev;
static ALCcontext* ctx;

namespace Blade
{
	namespace Audio
	{
		bool InitAudio() noexcept
		{
			if (dev)
			{
				// Already initiated.
				return true;
			}

			dev = alcOpenDevice(nullptr);
			if (!dev)
			{
				BLADE_ERROR("Failed to open OpenAL device\n");
				return false;
			}

			if (ctx)
			{
				return true;
			}

			ctx = alcCreateContext(dev, nullptr);
			if (!ctx)
			{
				BLADE_ERROR("Failed to create context\n");
				alcCloseDevice(dev);
				return false;
			}

			alcMakeContextCurrent(ctx);

			// Clear error state.
			alGetError();

			return true;
		}

		void DestroyAudio() noexcept
		{
			alcMakeContextCurrent(nullptr);

			if (ctx)
			{
				alcDestroyContext(ctx);
			}

			if (dev)
			{
				alcCloseDevice(dev);
			}
		}

		void SetAudioListener(const Mat4f& xform) noexcept
		{
			float pos[3], orient[6];

			pos[0] = xform[0][3];
			pos[1] = xform[1][3];
			pos[2] = xform[2][3];

			orient[0] = xform[0][2];
			orient[1] = xform[1][2];
			orient[2] = -xform[2][2];

			orient[3] = xform[0][1];
			orient[4] = xform[1][1];
			orient[5] = xform[2][1];

			alListenerfv(AL_POSITION, pos);
			alListenerfv(AL_ORIENTATION, orient);
		}
	}
}
