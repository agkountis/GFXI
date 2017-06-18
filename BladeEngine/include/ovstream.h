#ifndef OVSTREAM_H_
#define OVSTREAM_H_

#include <vorbis/vorbisfile.h>
#include "stream.h"

namespace Blade
{
	/**
	 * \brief Represents an AudioStream that streams .ogg files.
	 */
	class OggVorbisStream : public AudioStream {
	private:
		OggVorbis_File m_Vf;
		bool m_Vfopen;
		std::mutex m_Mutex;

		bool MoreSamples(AudioStreamBuffer *buf) noexcept override;

	public:
		OggVorbisStream();
		virtual ~OggVorbisStream();

		/**
		 * \brief Opens the specified .ogg file.
		 * \param fname The file name of the .ogg file.
		 * \return TRUE if successful, FALSE otherwise.
		 */
		bool Open(const char *fname) noexcept;

		/**
		 * \brief Closes the .ogg file.
		 */
		void Close() noexcept;

		void Play(AudioPlaymode mode) noexcept override;

		void Rewind() noexcept override;
	};
}

#endif  // OVSTREAM_H_
