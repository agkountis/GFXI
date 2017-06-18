#ifndef SAMPLE_H_
#define SAMPLE_H_
#include "resource.h"


namespace Blade
{
	/**
	 * \brief Represents an audio sample.
	 * \details Mainly used for short duration sound effects.
	 */
	class AudioSample : public Resource
	{
	private:
		unsigned int m_AlBuffer;

		void Destroy();

	public:
		AudioSample();
		~AudioSample();

		/**
		 * \brief Loads the specified file and creates an audio sample.
		 * \param fileName The file name of the audio sample.
		 * \return TRUE if secessful, FALSE otherwise.
		 */
		bool Load(const std::wstring& fileName) noexcept override;

		/**
		 * \brief Returns the index of the buffer as specified by OpenAL.
		 * \return The index of the buffer.
		 */
		unsigned int GetBuffer() const noexcept;
	};
}


#endif	// SAMPLE_H_
