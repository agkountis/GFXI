#ifndef BLADE_VBO_H_
#define BLADE_VBO_H_
#include <vector>
#include "vertex.h"

namespace Blade
{
	enum class PrimitiveTopology
	{
		TRIANGLE_LIST,
		TRIANGLE_STRIP
	};

	/*
	\brief Vertex buffer object of the engine.
	*/
	class VBO
	{
	private:
		/*
		\brief Number of vertex of the VBO
		*/
		unsigned int m_VertexCount = 0;

		/*
		\brief Primitive topology of the vertex buffer object
		*/
		PrimitiveTopology m_PrimitiveTopology{ PrimitiveTopology::TRIANGLE_LIST };

	public:
		VBO() = default;

		virtual ~VBO();

		void SetVertexCount(const unsigned int vertexCount) noexcept
		{
			m_VertexCount = vertexCount;
		}

		unsigned int GetVertexCount() const noexcept
		{
			return m_VertexCount;
		}

		void SetPrimitiveTopology(PrimitiveTopology primitiveTopology) noexcept
		{
			m_PrimitiveTopology = primitiveTopology;
		}

		PrimitiveTopology GetPrimitiveTopology() const noexcept
		{
			return m_PrimitiveTopology;
		}

		virtual bool Create(const std::vector<Vertex>& vertices, PrimitiveTopology primitiveTopology) noexcept = 0;

		virtual void Bind() const noexcept = 0;

		virtual void Draw() const noexcept = 0;
	};
}

#endif //BLADE_VBO_H_
