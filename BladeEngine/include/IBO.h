#ifndef BLADE_IBO_H_
#define BLADE_IBO_H_
#include <vector>

namespace Blade
{
	/*
	\brief The index buffer object class of the engine
	*/
	class IBO
	{
	private:
		/*
		\brief the index counter of the IBO
		*/
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

		/*
		\brief Create a new IBO from a vector of indices
		\param indices The indices vector to store inside the IBO
		*/
		virtual bool Create(const std::vector<unsigned int>& indices) noexcept = 0;

		/*
		\brief Bind the current IBO
		*/
		virtual void Bind() const noexcept = 0;

		/*
		\brief Draw the IBO
		*/
		virtual void Draw() const noexcept = 0;
	};
}

#endif //BLADE_IBO_H_
