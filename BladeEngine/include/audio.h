#ifndef AUDIO_H_
#define AUDIO_H_
#include "types.h"

namespace Blade
{
	/**
	 * \brief Contains initialization functions and other utilities.
	 */
	namespace Audio
	{
		/**
		 * \brief Initializes the audio library.
		 * \return TRUE if successful, FALSE otherwise.
		 */
		bool InitAudio() noexcept;

		/**
		 * \brief Cleans up the audio library.
		 */
		void DestroyAudio() noexcept;

		/**
		 * \brief Specified the world position of the audio listener.
		 * \param xform The transformation of the audio listener.
		 */
		void SetAudioListener(const Mat4f& xform) noexcept;
	}
}

#endif  // AUDIO_H_
