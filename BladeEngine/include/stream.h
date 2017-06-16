#ifndef STREAM_H_
#define STREAM_H_
#include <thread>
#include <mutex>
#include "types.h"

#define AUDIO_BUFFER_MSEC		1000
// TODO should the sampling rate be hardcoded?
#define AUDIO_BUFFER_SAMPLES	(AUDIO_BUFFER_MSEC * 44100 / 1000)
// TODO unhardcode the channels number
#define AUDIO_BUFFER_BYTES		(AUDIO_BUFFER_SAMPLES * 2 * 2)

namespace Blade
{
	enum AudioPlaymode
	{
		AUDIO_PLAYMODE_ONCE,
		AUDIO_PLAYMODE_LOOP
	};

	struct AudioStreamBuffer
	{
		Byte samples[AUDIO_BUFFER_BYTES];

		int sampleCount;
		int channels;
		int sampleRate;
	};

	class AudioStream
	{
	private:
		std::thread m_PlayThread;

		std::mutex m_Mutex;

		float m_InitialVolume;

		float m_Volume;

		bool m_Done;

		bool m_Loop;

		unsigned int m_PollInterval;

		unsigned int m_ALSource;

		virtual bool MoreSamples(AudioStreamBuffer* buf) noexcept = 0;

	public:
		void PollLoop() noexcept;

		AudioStream();

		virtual ~AudioStream();

		void SetVolume(float vol) noexcept;

		float GetVolume() const noexcept;

		void SetPlaybackVolume(float vol) noexcept;

		float GetPlaybackVolume() const noexcept;

		virtual void Play(AudioPlaymode mode) noexcept;

		virtual void Stop() noexcept;

		virtual void Rewind() noexcept = 0;

		virtual bool IsPlaying() const noexcept;

		virtual bool IsLooping() const noexcept;

		// TODO
		virtual int FreqCount(int bin) const noexcept;

		// frequency range in hertz
		virtual int FreqCount(int range_start, int range_end) const noexcept;
	};
}

#endif  // AUDIO_STREAM_H_
