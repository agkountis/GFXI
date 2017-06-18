#ifndef SOURCE_H_
#define SOURCE_H_

#include "sample.h"
#include "types.h"

namespace Blade
{
	/**
	 * \brief Represents an audio source in the world.
	 */
	class AudioSource
	{
	private:
		unsigned int m_Alsrc;

		const AudioSample* m_Sample;

		float m_Volume;

	public:
		AudioSource();

		~AudioSource();

		/**
		 * \brief Sets the AudioSample to be played.
		 * \param sample The AudioSample to be played.
		 */
		void SetSample(const AudioSample* sample) noexcept;

		/**
		 * \brief Returns a pointer to the AudioSample of the audio source.
		 * \return The AudioSample to be played.
		 */
		const AudioSample* GetSample() const noexcept;

		/**
		 * \brief Sets the position of the AudioSource.
		 * \param pos The position of the AudioSource int he world.
		 * \param viewspace A flag that determines if the position provided is in view space.
		 */
		void SetPosition(const Vec3f& pos, bool viewspace = false) const noexcept;

		/**
		 * \brief Returns the world position of the AudioSource.
		 * \return The world position of the AudioSource.
		 */
		Vec3f GetPosition() const noexcept;

		/**
		 * \brief Sets the volume of the audio source.
		 * \param vol The volume of the audio source.
		 */
		void SetVolume(float vol) noexcept;

		/**
		 * \brief Returns the volume of the audio source.
		 * \return The volume of the audio source.
		 */
		float GetVolume() const noexcept;

		/**
		 * \brief Adjusts the volume fo the source with the specified value.
		 * \param vol The volume to be set.
		 */
		void SetPlaybackVolume(float vol) const noexcept;

		/**
		 * \brief Returns the current volume of the audio source.
		 * \return The current volume of the audio source.
		 */
		float GetPlaybackVolume() const noexcept;

		/**
		 * \brief Sets the looping state of the audio source.
		 * \param state The looping state of the audio source.
		 */
		void SetLooping(bool state) const noexcept;

		/**
		 * \brief Sets the reference distance of the audio source.
		 * \details The reference distance is a value that regulates sound attenuation.
		 * \param rdist The referce distance of the audio source.
		 */
		void SetReferenceDist(float rdist) const noexcept;

		/**
		 * \brief Returns the current reference distance.
		 * \return The reference distance.
		 */
		float GetReferenceDist() const noexcept;

		/**
		 * \brief Sets the max distance after which audio sources are not attenuated.
		 * \param dist The distance to be set.
		 */
		void SetMaxDist(float dist) const noexcept;

		/**
		 * \brief Returns the max distance after which the audio sources are nto attenuated.
		 * \return The max distance after which the audio sources are nto attenuated.
		 */
		float GetMaxDist() const noexcept;

		/**
		 * \brief Checks if the audio source is playing.
		 * \return TRUE if the audio source is playing, FALSE otherwise.
		 */
		bool IsPlaying() const noexcept;

		/**
		 * \brief 
		 * \return TRUE if the audio source is paused, FALSE otherwise.
		 */
		bool IsPaused() const noexcept;

		/**
		 * \brief Starts playback of the audio source.
		 */
		void Play() const noexcept;

		/**
		 * \brief Stops playback of the audio source.
		 */
		void Stop() const noexcept;

		/**
		 * \brief Pauses playback of the audio source.
		 */
		void Pause() const noexcept;
	};
}

#endif	// SOURCE_H_
