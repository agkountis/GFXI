#ifndef BLADE_IBO_H_
#define BLADE_IBO_H_
#include <vector>

namespace Blade
{
	class IBO
	{
	private:
		unsigned int m_IndexCount{ 0 };

	public:
		IBO() = default;

		virtual ~IBO();

		void SetIndexCount(unsigned int idxCount) noexcept
		{
			m_IndexCount = idxCount;
		}

		unsigned int GetIndexCount() const noexcept
		{
			return m_IndexCount;
		}

		virtual bool Create(const std::vector<unsigned int>& indices) noexcept = 0;

		virtual void Bind() const noexcept = 0;

		virtual void Draw() const noexcept = 0;
	};
}

#endif //BLADE_IBO_H_
