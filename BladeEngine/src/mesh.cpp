#include "mesh.h"
#include "d3d/D3D11_VBO.h"
#include "d3d/D3D11_IBO.h"

namespace Blade
{
	Mesh::Mesh()
	{
#ifdef BLADE_BUILD_D3D
		m_Vbo = std::make_unique<D3D11VBO>();
		m_Ibo = std::make_unique<D3D11IBO>();
#else
		//GL versions here
#endif
	}

	VBO* Mesh::GetVbo() const noexcept
	{
		return m_Vbo.get();
	}

	IBO* Mesh::GetIbo() const noexcept
	{
		return m_Ibo.get();
	}

	size_t Mesh::GetVertexCount() const noexcept
	{
		return m_Vertices.size();
	}

	size_t Mesh::GetIndexCount() const noexcept
	{
		return m_Indices.size();
	}

	void Mesh::SetName(const std::string& name) noexcept
	{
		m_Name = name;
	}

	const std::string& Mesh::GetName() const noexcept
	{
		return m_Name;
	}

	void Mesh::InitiazeBufferObjects(PrimitiveTopology primitive_topology) const noexcept
	{
		if (m_Vertices.size())
		{
			m_Vbo->Create(m_Vertices, primitive_topology);
		}

		if (m_Indices.size())
		{
			m_Ibo->Create(m_Indices);
		}
	}

	void Mesh::SetVertexData(const Vertex* vertices, int vertex_count) noexcept
	{
		m_Vertices.resize(vertex_count);
		memcpy(m_Vertices.data(), vertices, sizeof(Vertex) * vertex_count);
	}

	Vertex* Mesh::GetVertexData() const noexcept
	{
		return const_cast<Vertex*>(m_Vertices.data());
	}

	void Mesh::AddVertex(const Vertex& vertex) noexcept
	{
		m_Vertices.push_back(vertex);
	}

	void Mesh::SetIndexData(const unsigned int* indices, int index_count) noexcept
	{
		m_Indices.resize(index_count);
		memcpy(m_Indices.data(), indices, sizeof(unsigned int) * index_count);
	}

	unsigned int* Mesh::GetIndexData() const noexcept
	{
		return const_cast<unsigned int*>(m_Indices.data());
	}

	void Mesh::AddIndex(unsigned int index) noexcept
	{
		m_Indices.push_back(index);
	}

	bool Mesh::Load(const std::wstring& file_name) noexcept
	{
		//TODO: implement loading.
		return true;
	}

	void Mesh::GenerateIndices(VertexWinding winding) noexcept
	{
		if (m_Indices.size())
		{
			return;
		}

		int quad_count = m_Vertices.size() / 4;
		int triangle_count = quad_count * 2;

		m_Indices.resize(triangle_count * 3);

		for (int i = 0, j = 0; i < m_Indices.size(); i += 6 , j += 4)
		{
			m_Indices[i] = j;
			switch (winding)
			{
			case VertexWinding::CLOCKWISE:
				m_Indices[i + 1] = m_Indices[i + 4] = j + 1;
				m_Indices[i + 2] = m_Indices[i + 3] = j + 2;
				break;
			case VertexWinding::ANTICLOCKWISE:
				m_Indices[i + 1] = m_Indices[i + 4] = j + 2;
				m_Indices[i + 2] = m_Indices[i + 3] = j + 1;
				break;
			default:
				break;
			}

			m_Indices[i + 5] = j + 3;
		}
	}
}
