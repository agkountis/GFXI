#ifndef BLADE_RESOURCE_H_
#define BLADE_RESOURCE_H_
#include <string>

namespace Blade
{
	class Resource
	{
	private:
		unsigned int m_Id;

	public:
		Resource() : m_Id{ 0 }
		{
		}

		explicit Resource(unsigned int id) : m_Id{ id }
		{
		}

		virtual ~Resource();

		unsigned int GetId() const noexcept
		{
			return m_Id;
		}

		void SetId(unsigned int id) noexcept
		{
			m_Id = id;
		}

		virtual bool Load(const std::wstring& fileName) noexcept = 0;
	};
}

#endif //BLADE_RESOURCE_H_
