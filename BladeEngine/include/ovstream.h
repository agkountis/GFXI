#ifndef OVSTREAM_H_
#define OVSTREAM_H_

#include <vorbis/vorbisfile.h>
#include "stream.h"

namespace Blade
{
	class OggVorbisStream : public AudioStream {
	private:
		OggVorbis_File m_Vf;
		bool m_Vfopen;
		std::mutex m_Mutex;

		bool MoreSamples(AudioStreamBuffer *buf) noexcept override;

	public:
		OggVorbisStream();
		virtual ~OggVorbisStream();

		bool Open(const char *fname) noexcept;
		void Close() noexcept;

		void Play(AudioPlaymode mode) noexcept override;
		void Rewind() noexcept override;
	};
}

#endif  // OVSTREAM_H_
