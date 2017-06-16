#include <stdio.h>
#include <assert.h>
#include "ovstream.h"
#include "trace.h"
#include <string>

namespace Blade
{
	OggVorbisStream::OggVorbisStream()
	{
		m_Vfopen = false;
	}

	OggVorbisStream::~OggVorbisStream()
	{
		Close();
	}

	bool OggVorbisStream::Open(const char* fname) noexcept
	{
		Close();

		m_Mutex.lock();

		std::string fpath = fname;
		printf("opening ogg/vorbis stream: %s -> %s\n", (fname && *fname) ? fname : "<not found>", (!fpath.empty()) ? fpath.c_str() : "<not found>");

		if (fpath.empty() || ov_fopen(fpath.c_str(), &m_Vf) != 0)
		{
			printf("failed to open ogg/vorbis stream: %s\n", fname ? fname : "<not found>");
			m_Mutex.unlock();
			return false;
		}

		m_Vfopen = true;

		m_Mutex.unlock();

		return true;
	}

	void OggVorbisStream::Close() noexcept
	{
		std::lock_guard<std::mutex> lock{ m_Mutex };

		if (m_Vfopen)
		{
			ov_clear(&m_Vf);
			m_Vfopen = false;
		}
	}

	void OggVorbisStream::Play(AudioPlaymode mode) noexcept
	{
		if (m_Vfopen)
		{
			AudioStream::Play(mode);
		}
		else
		{
			BLADE_ERROR("Failed to play audio track.");
		}
	}

	void OggVorbisStream::Rewind() noexcept
	{
		std::lock_guard<std::mutex> lock{ m_Mutex };

		if (m_Vfopen)
		{
			int res = ov_raw_seek(&m_Vf, 0);

			if (res)
			{
				switch (res)
				{
				case OV_ENOSEEK:
					BLADE_ERROR("Bitstream not seekable.");
					break;
				case OV_EINVAL:
					BLADE_ERROR("Invalid argument value; possibly called with an OggVorbis_File structure that isn't open.");
					break;
				case OV_EREAD:
					BLADE_ERROR("A read from media returned an error.");
					break;
				case OV_EFAULT:
					BLADE_ERROR("Internal logic fault; indicates a bug or heap/stack corruption.");
					break;
				case OV_EBADLINK:
					BLADE_ERROR("Invalid stream section supplied to libvorbisfile, or the requested link is corrupt.");
					break;
				default:
					break;
				}
			}

			BLADE_TRACE("Rewinding stream.");
		}
		else
		{
			BLADE_WARNING("Stream file not open. Cannot rewind.");
		}
	}

	bool OggVorbisStream::MoreSamples(AudioStreamBuffer* buf) noexcept
	{
		m_Mutex.lock();

		vorbis_info* vinfo = ov_info(&m_Vf, -1);
		buf->channels = vinfo->channels;
		buf->sampleRate = vinfo->rate;
		assert(buf->channels == 2);
		assert(buf->sampleRate == 44100);

		long bufsz = AUDIO_BUFFER_BYTES;
		long total_read = 0;
		while (total_read < bufsz)
		{
			int bitstream;
			long rd = ov_read(&m_Vf, buf->samples + total_read, bufsz - total_read, 0, 2, 1, &bitstream);

			if (!rd)
			{
				bufsz = total_read;
			}
			else
			{
				total_read += rd;
			}
		}

		if (!total_read)
		{
			BLADE_TRACE("No more samples to read.");
			buf->sampleCount = 0;
			m_Mutex.unlock();
			return false;
		}

		buf->sampleCount = bufsz / vinfo->channels / 2;
		m_Mutex.unlock();
		return true;
	}
}
