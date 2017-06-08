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
	/*
	\brief Defines vertex winding order
	*/
	enum class VertexWinding
	{
		CLOCKWISE,
		ANTICLOCKWISE
	};

	/*
	\brief Mesh class of the engine is a resource.
	*/
	class Mesh : public Resource
	{
	private:
		/*
		\brief Vector of indices of the mesh
		*/
		std::vector<Vertex> m_Vertices;
		/*
		\brief Vector of indices of the mesh
		*/
		std::vector<unsigned int> m_Indices;

		/*
		\brief VBO of the mesh
		*/
		std::unique_ptr<VBO> m_Vbo;

		/*
		\brief IBO of the mesh
		*/
		std::unique_ptr<IBO> m_Ibo;

		/*
		\brief Name of the mesh
		\details This can be used to ask to the resource manager a particular mesh.
		*/
		std::string m_Name;

	public:
		Mesh();

		Mesh(const Mesh& other) = default;

		Mesh& operator=(const Mesh& other) = default;

		VBO* GetVbo() const noexcept;

		IBO* GetIbo() const noexcept;

		size_t GetVertexCount() const noexcept;

		size_t GetIndexCount() const noexcept;

		void SetName(const std::string& name) noexcept;

		const std::string& GetName() const noexcept;

		void InitiazeBufferObjects(PrimitiveTopology primitiveTopology = PrimitiveTopology::TRIANGLE_LIST) const noexcept;

		void SetVertexData(const Vertex* vertices, int vertexCount) noexcept;

		Vertex* GetVertexData() const noexcept;

		void AddVertex(const Vertex& vertex) noexcept;

		void SetIndexData(const unsigned int* indices, int indexCount) noexcept;

		unsigned int* GetIndexData() const noexcept;

		void AddIndex(unsigned int index) noexcept;

		bool Load(const std::wstring& fileName) noexcept override;

		/*
		\brief Generates indices of the mesh
		*/
		void GenerateIndices(VertexWinding winding) noexcept;
	};
}

#endif //BLADE_MESH_H_
