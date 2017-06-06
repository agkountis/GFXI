#ifndef BLADE_MESH_H_
#define BLADE_MESH_H_
#include <vector>
#include "vertex.h"
#include "VBO.h"
#include "IBO.h"
#include <memory>
#include "resource.h"

namespace Blade
{
	enum class VertexWinding
	{
		CLOCKWISE,
		ANTICLOCKWISE
	};

	class Mesh : public Resource
	{
	private:
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;

		std::unique_ptr<VBO> m_Vbo;
		std::unique_ptr<IBO> m_Ibo;

		const std::string m_Name;

	public:
		Mesh();

		Mesh(const Mesh& other) = default;

		Mesh& operator=(const Mesh& other) = default;

		VBO* GetVbo() const noexcept
		{
			return m_Vbo.get();
		}

		IBO* GetIbo() const noexcept
		{
			return m_Ibo.get();
		}

		size_t GetVertexCount() const noexcept
		{
			return m_Vertices.size();
		}

		size_t GetIndexCount() const noexcept
		{
			return m_Indices.size();
		}

		void InitiazeBufferObjects(PrimitiveTopology primitiveTopology = PrimitiveTopology::TRIANGLE_LIST) const noexcept;

		void SetVertexData(const Vertex* vertices, int vertexCount) noexcept;

		Vertex* GetVertexData() const noexcept;

		void AddVertex(const Vertex& vertex) noexcept;

		void SetIndexData(const unsigned int* indices, int indexCount) noexcept;

		unsigned int* GetIndexData() const noexcept;

		void AddIndex(unsigned int index) noexcept;

		bool Load(const std::wstring& fileName) noexcept override;

		void GenerateIndices(VertexWinding winding) noexcept;
	};
}

#endif //BLADE_MESH_H_
