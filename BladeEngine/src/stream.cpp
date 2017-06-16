#include <stdio.h>
#include <assert.h>
#include "openal.h"
#include "stream.h"
#include "trace.h"
#include "timer.h"
#include <string>

namespace Blade
{
	static ALenum alformat(AudioStreamBuffer* buf) noexcept
	{
		return buf->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	}

	AudioStream::AudioStream()
		: m_InitialVolume{ 1.0 },
		  m_Volume{ 1.0 },
		  m_Done{ false },
		  m_Loop{ false },
		  m_PollInterval{ 250 },
		  m_ALSource{ 0 }
	{
	}

	AudioStream::~AudioStream()
	{
		AudioStream::Stop();
	}

	void AudioStream::SetVolume(float vol) noexcept
	{
		m_InitialVolume = vol;
	}

	float AudioStream::GetVolume() const noexcept
	{
		return m_InitialVolume;
	}

	void AudioStream::SetPlaybackVolume(float vol) noexcept
	{
		m_Volume = vol;
	}

	float AudioStream::GetPlaybackVolume() const noexcept
	{
		return m_Volume;
	}

	static void* thread_func(void* arg) noexcept
	{
		AudioStream* astr = static_cast<AudioStream*>(arg);
		astr->PollLoop();
		return nullptr;
	}

	void AudioStream::Play(AudioPlaymode mode) noexcept
	{
		m_Loop = mode == AUDIO_PLAYMODE_LOOP;
		m_Done = false;

		try
		{
			m_PlayThread = std::thread{ std::bind(thread_func, this) };
		}
		catch (...)
		{
			BLADE_ERROR("failed to create music playback thread\n");
		}
	}

	void AudioStream::Stop() noexcept
	{
		m_Mutex.lock();

		if (m_ALSource)
		{
			m_Done = true;
			alSourceStop(m_ALSource);
			BLADE_TRACE("Waiting for the music thread to stop.");
			m_Mutex.unlock();
			m_PlayThread.join();
		}
		else
		{
			m_Mutex.unlock();
		}
	}

	// thread function
	void AudioStream::PollLoop() noexcept
	{
		static const int bufferCount = 3;
		unsigned int alBuffers[bufferCount];

		m_Mutex.lock();

		alGenSources(1, &m_ALSource);

		alSourcei(m_ALSource, AL_LOOPING, AL_FALSE);

		alSourcef(m_ALSource, AL_GAIN, m_InitialVolume);

		alGenBuffers(bufferCount, alBuffers);

		AudioStreamBuffer* audioStreamBuffer = new AudioStreamBuffer;

		for (int i = 0; i < bufferCount; i++)
		{
			if (MoreSamples(audioStreamBuffer))
			{
				int bufsz = audioStreamBuffer->sampleCount * audioStreamBuffer->channels * 2; // 2 is for 16bit samples

				alBufferData(alBuffers[i], alformat(audioStreamBuffer), audioStreamBuffer->samples, bufsz, audioStreamBuffer->sampleRate);

				if (alGetError())
				{
					BLADE_ERROR("failed to load sample data into OpenAL buffer.");
				}

				alSourceQueueBuffers(m_ALSource, 1, alBuffers + i);

				if (alGetError())
				{
					BLADE_ERROR("failed to start streaming audio buffers");
				}
			}
			else
			{
				break;
			}
		}

		// start playback
		alSourcePlay(m_ALSource);

		while (!m_Done)
		{
			/* find out how many (if any) of the queued buffers are
			* done, and free to be reused.
			*/
			alSourcef(m_ALSource, AL_GAIN, m_Volume);
			int num_buf_done;
			alGetSourcei(m_ALSource, AL_BUFFERS_PROCESSED, &num_buf_done);

			for (int i = 0; i < num_buf_done; i++)
			{
				int err;
				// unqueue a buffer...
				unsigned int buf_id;
				alSourceUnqueueBuffers(m_ALSource, 1, &buf_id);

				if ((err = alGetError()))
				{
					fprintf(stderr, "failed to unqueue used buffer (error: %x)\n", err);
					num_buf_done = i;
					break;
				}

				int looping;

				alGetSourcei(m_ALSource, AL_LOOPING, &looping);
				assert(looping == AL_FALSE);
				int cur_buf;
				alGetSourcei(m_ALSource, AL_BUFFER, &cur_buf);
				if (static_cast<unsigned int>(cur_buf) == buf_id)
				{
					continue;
				}

				// if there are more data, fill it up and requeue it
				if (MoreSamples(audioStreamBuffer))
				{
					int bufsz = audioStreamBuffer->sampleCount * audioStreamBuffer->channels * 2; // 2 is for 16bit samples
					alBufferData(buf_id, alformat(audioStreamBuffer), audioStreamBuffer->samples, bufsz, audioStreamBuffer->sampleRate);
					if ((err = alGetError()))
					{
						fprintf(stderr, "failed to load sample data into OpenAL buffer (error: %x)\n", err);
					}

					alSourceQueueBuffers(m_ALSource, 1, &buf_id);
					if (alGetError())
					{
						fprintf(stderr, "failed to start streaming audio buffers\n");
					}
				}
				else
				{
					// no more data...
					if (m_Loop)
					{
						Rewind();
						alSourceQueueBuffers(m_ALSource, 1, &buf_id);
					}
					else
					{
						m_Done = true;
					}
				}
			}

			if (num_buf_done)
			{
				// make sure playback didn't stop
				int state;
				alGetSourcei(m_ALSource, AL_SOURCE_STATE, &state);
				if (state != AL_PLAYING)
				{
					alSourcePlay(m_ALSource);
				}
			}

			m_Mutex.unlock();

			std::chrono::duration<unsigned int, std::milli> dur(m_PollInterval);
			std::this_thread::sleep_for(dur);

			m_Mutex.lock();
		}


		// done with the data, wait for the source to stop playing before cleanup
		int state;

		while (alGetSourcei(m_ALSource, AL_SOURCE_STATE, &state) , state == AL_PLAYING)
		{
			std::this_thread::yield();
		}

		alDeleteBuffers(bufferCount, alBuffers);
		alDeleteSources(1, &m_ALSource);
		m_ALSource = 0;
		m_Mutex.unlock();

		delete audioStreamBuffer;
	}

	bool AudioStream::IsPlaying() const noexcept
	{
		return !m_Done;
	}

	bool AudioStream::IsLooping() const noexcept
	{
		return m_Loop;
	}

	int AudioStream::FreqCount(int bin) const noexcept
	{
		return 0; // TODO
	}

	// frequency range in hertz
	int AudioStream::FreqCount(int range_start, int range_end) const noexcept
	{
		return 0; // TODO
	}
}
