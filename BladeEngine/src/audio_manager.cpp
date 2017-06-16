#include <iostream>
#include "audio_manager.h"
#include "openal.h"
#include "../../BattleArena/include/battle_arena_application.h"
#include "audio.h"

namespace Blade
{
	StreamPlaylist::StreamPlaylist()
	{
		loop = false;
		started = false;
	}

	SamplePlaylist::SamplePlaylist()
	{
		loop = false;
	}

	AudioManager::AudioManager()
	{
		for (unsigned int i = 0; i < NUM_STREAMS; i++)
		{
			m_Streams[i] = nullptr;
		}

		for (unsigned int i = 0; i < NUM_SOURCES; i++)
		{
			m_Sources[i] = nullptr;
		}

		m_SourcesVolume = 1.0;
		m_StreamsVolume = 1.0;
		m_MasterVolume = 1.0;

		Audio::InitAudio();
	}

	AudioManager::~AudioManager()
	{
		Cleanup();
		Audio::DestroyAudio();
	}

	/*Private Functions-------------*/
	OggVorbisStream* AudioManager::RequestStream(int* stream_idx)
	{
		for (unsigned int i = 0; i < NUM_STREAMS; i++)
		{
			if (m_Streams[i] && !m_Streams[i]->IsPlaying())
			{
				m_Streams[i]->Close();
				if (stream_idx)
					*stream_idx = i;
				return m_Streams[i];
			}
		}

		for (unsigned int i = 0; i < NUM_STREAMS; i++)
		{
			if (!m_Streams[i])
			{
				m_Streams[i] = new OggVorbisStream;
				if (stream_idx)
					*stream_idx = i;
				return m_Streams[i];
			}
		}

		std::cerr << "All available streams are allocated and currenlty playing! Cannot open a new stream!" << std::endl;
		return nullptr;
	}

	AudioSource* AudioManager::RequestSource(int* source_idx)
	{
		for (unsigned int i = 0; i < NUM_SOURCES; i++)
		{
			if (m_Sources[i] && !m_Sources[i]->IsPlaying())
			{
				if (source_idx)
					*source_idx = i;
				return m_Sources[i];
			}
		}

		for (unsigned int i = 0; i < NUM_SOURCES; i++)
		{
			if (!m_Sources[i])
			{
				m_Sources[i] = new AudioSource;
				if (source_idx)
					*source_idx = i;
				return m_Sources[i];
			}
		}

		std::cerr << "Maximum number of sources allocated and are playing a sample! Cannot play the sample specified!" << std::endl;
		return nullptr;
	}

	void AudioManager::Cleanup()
	{
		for (unsigned int i = 0; i < NUM_STREAMS; i++)
		{
			if (m_Streams[i])
			{
				m_Streams[i]->Stop();
				m_Streams[i]->Close();
				delete m_Streams[i];
			}
		}

		for (unsigned int i = 0; i < NUM_SOURCES; i++)
		{
			if (m_Sources[i])
			{
				m_Sources[i]->Stop();
				delete m_Sources[i];
			}
		}
	}

	/*------------------------------*/

	void AudioManager::SetListenerPosition(const glm::vec3& pos)
	{
		float values[3] = { pos.x, pos.y, pos.z };
		alListenerfv(AL_POSITION, values);
	}

	void AudioManager::SetListenerOrientation(const glm::vec3& dir, const glm::vec3& up)
	{
		float values[6] = { dir.x, dir.y, dir.z, up.x, up.y, up.z };
		alListenerfv(AL_ORIENTATION, values);
	}

	void AudioManager::SetSourcesVolume(float volume)
	{
		if (volume < 0.0)
			volume = 0.0;

		if (volume > 1.0)
			volume = 1.0;

		m_SourcesVolume = volume;
	}

	void AudioManager::SetStreamsVolume(float volume)
	{
		if (volume < 0.0)
			volume = 0.0;

		if (volume > 1.0)
			volume = 1.0;

		m_StreamsVolume = volume;
	}

	void AudioManager::SetMasterVolume(float volume)
	{
		if (volume < 0.0)
			volume = 0.0;

		if (volume > 1.0)
			volume = 1.0;

		m_MasterVolume = volume;
	}

	OggVorbisStream* AudioManager::GetAudioStream(int idx)
	{
		if (idx < NUM_STREAMS && idx >= 0)
		{
			if (m_Streams[idx])
				return m_Streams[idx];
		}
		else
		{
			std::cerr << "Index out of array bounds! Max available streams ->" << NUM_STREAMS << std::endl;
		}
		return nullptr;
	}

	AudioSource* AudioManager::GetAudioSource(int idx)
	{
		if (idx < NUM_SOURCES && idx >= 0)
		{
			if (m_Sources[idx])
				return m_Sources[idx];
		}

		return nullptr;
	}

	AudioSource* AudioManager::GetAudioSource(AudioSample* sample)
	{
		for (unsigned int i = 0; i < NUM_SOURCES; i++)
		{
			const AudioSample* s = nullptr;
			if (m_Sources[i])
				s = m_Sources[i]->GetSample();

			if (s == sample)
			{
				return m_Sources[i];
			}
		}

		return nullptr;
	}

	void AudioManager::PlayStream(const std::wstring& fname, float volume, AudioPlaymode mode, int* stream_idx)
	{
		OggVorbisStream* stream = RequestStream(stream_idx);
		if (stream)
		{
			stream->Open(StringUtils::ToString(fname).c_str());
			stream->SetVolume(volume);
			stream->SetPlaybackVolume(volume);
			stream->Play(mode);
		}
	}

	void AudioManager::PlaySample(AudioSample* sample, float volume, AudioPlaymode mode, const glm::vec3& position, int* src_idx)
	{
		AudioSource* source = RequestSource(src_idx);
		if (source)
		{
			source->SetSample(sample);
			source->SetVolume(volume);
			source->SetPlaybackVolume(volume);
			source->SetLooping(static_cast<bool>(mode));
			source->SetPosition(position);
			source->Play();
		}
	}

	void AudioManager::PlayStreamPlaylist(StreamPlaylist* playlist, float volume)
	{
		OggVorbisStream* stream;

		if (!playlist->started)
		{
			stream = RequestStream(&playlist->stream_idx);
			if (stream)
			{
				playlist->it = playlist->files.begin();
				stream->Open((*playlist->it).c_str());
				stream->SetVolume(volume);
				stream->SetPlaybackVolume(volume);
				stream->Play(AUDIO_PLAYMODE_ONCE);
				++playlist->it;
				playlist->started = true;
			}
		}
		else
		{
			stream = GetAudioStream(playlist->stream_idx);
			if (stream && !stream->IsPlaying())
			{
				if (!(playlist->it == playlist->files.end()))
				{
					stream->Close();
					stream->Open((*playlist->it).c_str());
					stream->SetVolume(volume);
					stream->SetPlaybackVolume(volume);
					stream->Play(AUDIO_PLAYMODE_ONCE);
					++playlist->it;
				}
			}
		}

		if (playlist->loop && playlist->it == playlist->files.end())
			playlist->it = playlist->files.begin();
	}

	void AudioManager::PlaySamplePlaylist(SamplePlaylist* playlist, float volume)
	{
		AudioSource* src;

		if (!playlist->started)
		{
			src = RequestSource(&playlist->source_idx);
			if (src)
			{
				playlist->it = playlist->samples.begin();
				src->SetSample((*playlist->it));
				src->SetVolume(volume);
				src->SetPlaybackVolume(volume);
				src->Play();
				++playlist->it;
				playlist->started = true;
			}
		}
		else
		{
			src = GetAudioSource(playlist->source_idx);
			if (src && !src->IsPlaying())
			{
				if (!(playlist->it == playlist->samples.end()))
				{
					src->SetSample((*playlist->it));
					src->SetVolume(volume);
					src->SetPlaybackVolume(volume);
					src->Play();
					++playlist->it;
				}
			}
		}

		if (playlist->loop && playlist->it == playlist->samples.end())
			playlist->it = playlist->samples.begin();
	}

	void AudioManager::StopStream(int stream_idx)
	{
		if (stream_idx < 0)
			return;

		AudioStream* strm = GetAudioStream(stream_idx);
		if (strm && strm->IsPlaying())
			strm->Stop();
	}

	void AudioManager::StopSource(int source_idx)
	{
		if (source_idx < 0)
			return;

		AudioSource* src = GetAudioSource(source_idx);
		if (src && src->IsPlaying())
			src->Stop();
	}

	void AudioManager::StopStreams()
	{
		for (unsigned int i = 0; i < NUM_STREAMS; i++)
		{
			if (m_Streams[i] && m_Streams[i]->IsPlaying())
				m_Streams[i]->Stop();
		}
	}

	void AudioManager::StopSources()
	{
		for (unsigned int i = 0; i < NUM_SOURCES; i++)
		{
			if (m_Sources[i] && m_Sources[i]->IsPlaying())
				m_Sources[i]->Stop();
		}
	}

	void AudioManager::PauseStreams()
	{
	}

	void AudioManager::PauseSources()
	{
		for (unsigned int i = 0; i < NUM_SOURCES; i++)
		{
			if (m_Sources[i] && m_Sources[i]->IsPlaying())
				m_Sources[i]->Pause();
		}
	}

	void AudioManager::ResumeStreams()
	{
		//TODO
	}

	void AudioManager::ResumeSources()
	{
		for (unsigned int i = 0; i < NUM_SOURCES; i++)
		{
			if (m_Sources[i] && !m_Sources[i]->IsPlaying())
				m_Sources[i]->Play();
		}
	}


	void AudioManager::RegulateVolumes()
	{
		for (unsigned int i = 0; i < NUM_SOURCES; i++)
		{
			if (m_Sources[i])
			{
				float vol = m_Sources[i]->GetVolume() * m_SourcesVolume * m_MasterVolume;
				m_Sources[i]->SetPlaybackVolume(vol);
			}
		}

		for (unsigned int i = 0; i < NUM_STREAMS; i++)
		{
			if (m_Streams[i])
			{
				m_Streams[i]->SetPlaybackVolume(m_Streams[i]->GetVolume() * m_StreamsVolume * m_MasterVolume);
			}
		}
	}
}
