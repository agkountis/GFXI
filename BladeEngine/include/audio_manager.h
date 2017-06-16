#ifndef AUDIO_MANAGER_H_
#define AUDIO_MANAGER_H_
#include "ovstream.h"
#include "source.h"
#include <list>

#define NUM_STREAMS 4
#define NUM_SOURCES 128

namespace Blade
{
	struct StreamPlaylist
	{
		std::list<std::string> files;
		std::list<std::string>::iterator it;
		bool loop;
		bool started{ false };
		int stream_idx{ -1 };

		StreamPlaylist();
	};

	struct SamplePlaylist
	{
		std::list<AudioSample*> samples;
		std::list<AudioSample*>::iterator it;
		bool loop;
		bool started{ false };
		int source_idx{ -1 };

		SamplePlaylist();
	};

	class AudioManager
	{
	private:
		OggVorbisStream* m_Streams[NUM_STREAMS];

		AudioSource* m_Sources[NUM_SOURCES];

		float m_SourcesVolume{ 1.0f };

		float m_StreamsVolume{ 1.0f };

		float m_MasterVolume{ 1.0f };

		OggVorbisStream* RequestStream(int* stream_idx = nullptr);

		AudioSource* RequestSource(int* source_idx = nullptr);

		void Cleanup();

	public:
		AudioManager();

		~AudioManager();

		static void SetListenerPosition(const Vec3f& pos = Vec3f{ 0, 0, 0 });

		static void SetListenerOrientation(const Vec3f& dir, const Vec3f& up = Vec3f{ 0, 1, 0 });

		void SetSourcesVolume(float volume);

		void SetStreamsVolume(float volume);

		void SetMasterVolume(float volume);

		OggVorbisStream* GetAudioStream(int idx);

		AudioSource* GetAudioSource(int idx);

		AudioSource* GetAudioSource(AudioSample* sample);

		void PlayStream(const std::wstring& fname, float volume, AudioPlaymode mode, int* stream_idx = nullptr);

		void PlaySample(AudioSample* sample, float volume, AudioPlaymode mode, const Vec3f& position = Vec3f{ 0, 0, 0 }, int* src_idx = nullptr);

		void PlayStreamPlaylist(StreamPlaylist* playlist, float volume);

		void PlaySamplePlaylist(SamplePlaylist* playlist, float volume);

		void StopStream(int stream_idx);

		void StopSource(int source_idx);

		void StopStreams();

		void StopSources();

		void PauseStreams(); //TODO

		void PauseSources();

		void ResumeStreams(); //TODO

		void ResumeSources();

		void RegulateVolumes();
	};
}

#endif //AUDIO_MANAGER_H_
