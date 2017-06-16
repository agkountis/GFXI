#include "openal.h"
#include "source.h"

namespace Blade
{
	AudioSource::AudioSource()
		: m_Sample{ nullptr },
		  m_Volume{ 1.0f }
	{
		alGenSources(1, &m_Alsrc);
		alSourcei(m_Alsrc, AL_LOOPING, AL_FALSE);
	}

	AudioSource::~AudioSource()
	{
		if (m_Alsrc)
		{
			if (IsPlaying())
			{
				Stop();
			}

			alDeleteSources(1, &m_Alsrc);
		}
	}

	void AudioSource::SetSample(const AudioSample* sample) noexcept
	{
		Stop();

		if (sample)
		{
			if (!sample->GetBuffer())
			{
				fprintf(stderr, "%s: trying to attach null buffer!\n", __FUNCTION__);
				return;
			}
			alSourcei(m_Alsrc, AL_BUFFER, sample->GetBuffer());
		}

		this->m_Sample = sample;
	}

	const AudioSample* AudioSource::GetSample() const noexcept
	{
		return m_Sample;
	}

	void AudioSource::SetPosition(const Vec3f& pos, bool viewspace) const noexcept
	{
		alSourcei(m_Alsrc, AL_SOURCE_RELATIVE, viewspace ? AL_TRUE : AL_FALSE);
		alSource3f(m_Alsrc, AL_POSITION, pos.x, pos.y, pos.z);
	}

	Vec3f AudioSource::GetPosition() const noexcept
	{
		float pos[3];
		alGetSourcefv(m_Alsrc, AL_POSITION, pos);
		return Vec3f{ pos[0], pos[1], pos[2] };
	}

	void AudioSource::SetVolume(float vol) noexcept
	{
		m_Volume = vol;
	}

	float AudioSource::GetVolume() const noexcept
	{
		return m_Volume;
	}

	void AudioSource::SetPlaybackVolume(float vol) const noexcept
	{
		alSourcef(m_Alsrc, AL_GAIN, vol);
	}

	float AudioSource::GetPlaybackVolume() const noexcept
	{
		float vol;
		alGetSourcef(m_Alsrc, AL_GAIN, &vol);
		return vol;
	}

	void AudioSource::SetLooping(bool state) const noexcept
	{
		alSourcei(m_Alsrc, AL_LOOPING, state);
	}

	void AudioSource::SetReferenceDist(float rdist) const noexcept
	{
		alSourcef(m_Alsrc, AL_REFERENCE_DISTANCE, rdist);
	}

	float AudioSource::GetReferenceDist() const noexcept
	{
		float res;
		alGetSourcef(m_Alsrc, AL_REFERENCE_DISTANCE, &res);
		return res;
	}

	void AudioSource::SetMaxDist(float dist) const noexcept
	{
		alSourcef(m_Alsrc, AL_MAX_DISTANCE, dist);
	}

	float AudioSource::GetMaxDist() const noexcept
	{
		float res;
		alGetSourcef(m_Alsrc, AL_MAX_DISTANCE, &res);
		return res;
	}

	bool AudioSource::IsPlaying() const noexcept
	{
		int state;
		alGetSourcei(m_Alsrc, AL_SOURCE_STATE, &state);
		return state == AL_PLAYING;
	}

	bool AudioSource::IsPaused() const noexcept
	{
		int state;
		alGetSourcei(m_Alsrc, AL_SOURCE_STATE, &state);
		return state == AL_PAUSED;
	}

	void AudioSource::Play() const noexcept
	{
		if (m_Sample)
		{
			alSourcePlay(m_Alsrc);
		}
	}

	void AudioSource::Stop() const noexcept
	{
		if (m_Sample)
		{
			alSourceStop(m_Alsrc);
		}
	}

	void AudioSource::Pause() const noexcept
	{
		if (m_Sample)
		{
			alSourcePause(m_Alsrc);
		}
	}
}
