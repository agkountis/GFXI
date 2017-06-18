#ifndef AUDIO_MANAGER_H_
#define AUDIO_MANAGER_H_
#include "ovstream.h"
#include "source.h"
#include <list>

#define NUM_STREAMS 4
#define NUM_SOURCES 128

namespace Blade
{
	/**
	 * \brief Represents an AudioStream playlist.
	 * \details Used to play large soundtracks in sequence.
	 */
	struct StreamPlaylist
	{
		std::list<std::string> files;
		std::list<std::string>::iterator it;
		bool loop;
		bool started{ false };
		int stream_idx{ -1 };

		StreamPlaylist();
	};

	/**
	 * \brief Represents an AudioSample playlist.
	 */
	struct SamplePlaylist
	{
		std::list<AudioSample*> samples;
		std::list<AudioSample*>::iterator it;
		bool loop;
		bool started{ false };
		int source_idx{ -1 };

		SamplePlaylist();
	};

	/**
	 * \brief A class the provides an interface to play audio samples and audio streams.
	 */
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

		/**
		 * \brief Sets the position of the listener in the world.
		 * \param pos The position of the listener in world coordinates.
		 */
		static void SetListenerPosition(const Vec3f& pos = Vec3f{ 0, 0, 0 });

		/**
		 * \brief Sets the listener's orientation in the world.
		 * \param dir The direction of the listener.
		 * \param up The up vector.
		 */
		static void SetListenerOrientation(const Vec3f& dir, const Vec3f& up = Vec3f{ 0, 1, 0 });

		/**
		 * \brief Sets the specified volume to all the active AudioSources.
		 * \param volume The volume to be set.
		 */
		void SetSourcesVolume(float volume);

		/**
		 * \brief SEts the specified volume to all the active AudioStreams.
		 * \param volume The volume to be set.
		 */
		void SetStreamsVolume(float volume);

		/**
		 * \brief Sets the master volume of the audio.
		 * \remarks Applies to both audio sources and audio streams.
		 * \param volume The volume to be set.
		 */
		void SetMasterVolume(float volume);

		/**
		 * \brief Returns the specified audio stream from the array.
		 * \param idx The index of the audio stream in the array of audio streams.
		 * \return A pointer to the OggVorbisStream.
		 */
		OggVorbisStream* GetAudioStream(int idx);

		/**
		 * \brief Returns the specified audio source from the array.
		 * \param idx The index of the audio source in the array of audio sources.
		 * \return A pointer to the AudioSource.
		 */
		AudioSource* GetAudioSource(int idx);

		/**
		 * \brief Returns the AudioSource playing the specified AudioSample.
		 * \param sample A pointer to an AudioSample played by an AudioSource.
		 * \return The AudioSource playing the specified AudioSample.
		 */
		AudioSource* GetAudioSource(AudioSample* sample);

		/**
		 * \brief Starts playback of an AudioStream.
		 * \param fname The file name of the audio file to be streamed.
		 * \param volume The playback volume.
		 * \param mode The playback mode.
		 * \param stream_idx Used to specify a specific AudioStream from the array to be used for the playback.
		 */
		void PlayStream(const std::wstring& fname, float volume, AudioPlaymode mode, int* stream_idx = nullptr);

		/**
		 * \brief 
		 * \param sample The audio sample to be played.
		 * \param volume The playback volume.
		 * \param mode The playback mode.
		 * \param position The position of the audio source in world coordinates.
		 * \param src_idx Used to specify a specific AudioSource from the array to be used for the playback.
		 */
		void PlaySample(AudioSample* sample, float volume, AudioPlaymode mode, const Vec3f& position = Vec3f{ 0, 0, 0 }, int* src_idx = nullptr);

		/**
		 * \brief Starts playback of a StreamPLaylist.
		 * \param playlist The StreamPlaylist to play.
		 * \param volume The playback volume.
		 */
		void PlayStreamPlaylist(StreamPlaylist* playlist, float volume);

		/**
		 * \brief Starts the playback of a SamplePlaylist.
		 * \param playlist The SamplePlaylist to play.
		 * \param volume THe playback volume.
		 */
		void PlaySamplePlaylist(SamplePlaylist* playlist, float volume);

		/**
		 * \brief Stops playback of the audio stream with the specified index in the array.
		 * \param stream_idx The index of the stream in the array.
		 */
		void StopStream(int stream_idx);

		/**
		 * \brief Stops playback of the audio source with the specified index in the array.
		 * \param source_idx The index of the audio source in the array.
		 */
		void StopSource(int source_idx);

		/**
		 * \brief Stops playback of all the active audio streams.
		 */
		void StopStreams();

		/**
		 * \brief Stops the playback of all the active audio sources.
		 */
		void StopSources();

		/**
		 * \brief Pauses the playback of all the active audio streams.
		 */
		void PauseStreams(); //TODO

		/**
		 * \brief Pauses the playback of all the active audio sources.
		 */
		void PauseSources();

		/**
		 * \brief Resumes the playback of all the active audio streams.
		 */
		void ResumeStreams(); //TODO

		/**
		 * \brief Resumes the playback of all the active audio sources.
		 */
		void ResumeSources();

		/**
		 * \brief Applies the correct volume value to all active audio streams and audio sources.
		 */
		void RegulateVolumes();
	};
}

#endif //AUDIO_MANAGER_H_
