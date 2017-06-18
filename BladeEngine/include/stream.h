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
	/**
	 * \brief The playback mode of the specified audio.
	 */
	enum AudioPlaymode
	{
		AUDIO_PLAYMODE_ONCE,
		AUDIO_PLAYMODE_LOOP
	};

	/**
	 * \brief Represends an audio stream buffer.
	 * \details Used to stream large audio files into the engine.
	 */
	struct AudioStreamBuffer
	{
		Byte samples[AUDIO_BUFFER_BYTES];

		int sampleCount;
		int channels;
		int sampleRate;
	};

	/**
	 * \brief Represents a streamed audio file.
	 * \details Instead of loading the whole file in memory, this class
	 * streams data into the engine and plays it back.
	 */
	class AudioStream
	{
	private:
		/**
		 * \brief The thread that streams and plays the audio file.
		 */
		std::thread m_PlayThread;

		std::mutex m_Mutex;

		/**
		 * \brief Initial volume of the stream.
		 */
		float m_InitialVolume;

		/**
		 * \brief Additional volume control.
		 */
		float m_Volume;

		/**
		 * \brief Flag that determines if the stream has finish
		 */
		bool m_Done;

		bool m_Loop;

		unsigned int m_PollInterval;

		unsigned int m_ALSource;

		virtual bool MoreSamples(AudioStreamBuffer* buf) noexcept = 0;

	public:
		/**
		 * \brief Method that loops and pools for more samples from the file stream.
		 */
		void PollLoop() noexcept;

		AudioStream();

		virtual ~AudioStream();

		/**
		 * \brief Sets the initial volume of the playback.
		 * \param vol The volume value.
		 */
		void SetVolume(float vol) noexcept;

		/**
		 * \brief Returns the initial volume of the playback.
		 * \return The curretn volume of the playback.
		 */
		float GetVolume() const noexcept;

		/**
		 * \brief Sets the volume value used during playback.
		 * \param vol The volume value used during playback.
		 */
		void SetPlaybackVolume(float vol) noexcept;

		/**
		 * \brief Returns the volume value of the stream during playback.
		 * \return The volume value of the stream during playback.
		 */
		float GetPlaybackVolume() const noexcept;

		/**
		 * \brief Starts playback of the stream using the specified playback mode.
		 * \param mode The playback mode of the stream.
		 */
		virtual void Play(AudioPlaymode mode) noexcept;

		/**
		 * \brief Stop playback of the stream.
		 */
		virtual void Stop() noexcept;

		virtual void Rewind() noexcept = 0;

		/**
		 * \brief Checks if the stream is currently playing.
		 * \return TRUE if the stream is currently playing, FALSE otherwise.
		 */
		virtual bool IsPlaying() const noexcept;

		/**
		 * \brief Checks if the stream is in a loop state.
		 * \return TRUE if the stream is in a loop state, FALSE otherwise.
		 */
		virtual bool IsLooping() const noexcept;

		// TODO
		virtual int FreqCount(int bin) const noexcept;

		// frequency range in hertz
		virtual int FreqCount(int range_start, int range_end) const noexcept;
	};
}

#endif  // AUDIO_STREAM_H_
