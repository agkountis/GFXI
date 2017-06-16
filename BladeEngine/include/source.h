#ifndef SOURCE_H_
#define SOURCE_H_

#include "sample.h"
#include "types.h"

namespace Blade
{
	class AudioSource
	{
	private:
		unsigned int m_Alsrc;

		const AudioSample* m_Sample;

		float m_Volume;

	public:
		AudioSource();

		~AudioSource();

		void SetSample(const AudioSample* sample) noexcept;

		const AudioSample* GetSample() const noexcept;

		void SetPosition(const Vec3f& pos, bool viewspace = false) const noexcept;

		Vec3f GetPosition() const noexcept;

		void SetVolume(float vol) noexcept;

		float GetVolume() const noexcept;

		void SetPlaybackVolume(float vol) const noexcept;

		float GetPlaybackVolume() const noexcept;

		void SetLooping(bool state) const noexcept;

		void SetReferenceDist(float rdist) const noexcept;

		float GetReferenceDist() const noexcept;

		void SetMaxDist(float dist) const noexcept;

		float GetMaxDist() const noexcept;

		bool IsPlaying() const noexcept;

		bool IsPaused() const noexcept;

		void Play() const noexcept;

		void Stop() const noexcept;

		void Pause() const noexcept;
	};
}

#endif	// SOURCE_H_
