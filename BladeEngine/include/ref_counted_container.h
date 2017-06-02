#ifndef BLADE_REF_COUNTED_CONTAINER_H_
#define BLADE_REF_COUNTED_CONTAINER_H_

namespace Blade
{
	template <typename T>
	class RefCountedContainer
	{
	private:
		T* m_Data{ nullptr };
		int m_ReferenceCount{ 0 };

	public:
		explicit RefCountedContainer(T* item)
		{
			m_Data = item;
			AddReference();
		}

		~RefCountedContainer()
		{
			SubtractReference();

			if (!m_ReferenceCount)
			{
				delete m_Data;
			}
		}


		RefCountedContainer(const RefCountedContainer& other)
			: m_Data(other.m_Data),
			m_ReferenceCount(other.m_ReferenceCount)
		{
			AddReference();
		}

		explicit RefCountedContainer(RefCountedContainer&& other) noexcept = delete;

		RefCountedContainer& operator=(const RefCountedContainer& other)
		{
			if (this == &other)
			{
				return *this;
			}

			SubtractReference();

			if (!m_ReferenceCount)
			{
				delete m_Data;
			}

			m_Data = other.m_Data;
			m_ReferenceCount = other.m_ReferenceCount;

			AddReference();

			return *this;
		}

		RefCountedContainer& operator=(RefCountedContainer&& other) noexcept = delete;

		void AddReference() noexcept
		{
			++m_ReferenceCount;
		}

		void SubtractReference() noexcept
		{
			--m_ReferenceCount;
		}

		int GetReferenceCount() const noexcept
		{
			return m_ReferenceCount;
		}

		T* Get() const noexcept
		{
			return m_Data;
		}
	};
}

#endif //BLADE_REF_COUNTED_CONTAINER_H_
