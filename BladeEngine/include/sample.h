#ifndef SAMPLE_H_
#define SAMPLE_H_
#include "resource.h"


namespace Blade
{
	class AudioSample : public Resource
	{
	private:
		unsigned int m_AlBuffer;

		void Destroy();

	public:
		AudioSample();
		~AudioSample();

		bool Load(const std::wstring& fileName) noexcept override;

		unsigned int GetBuffer() const noexcept;
	};
}


#endif	// SAMPLE_H_
