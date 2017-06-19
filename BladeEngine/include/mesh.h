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
	/**
	 * \brief Defines vertex winding order
	 */
	enum class VertexWinding
	{
		CLOCKWISE,
		ANTICLOCKWISE
	};

	/**
	 * \brief Mesh class of the engine is a resource.
	 */
	class Mesh : public Resource
	{
	private:
		/**
		 * \brief Vector of indices of the mesh
		 */
		std::vector<Vertex> m_Vertices;
		/**
		 * \brief Vector of indices of the mesh
		 */
		std::vector<unsigned int> m_Indices;

		/**
		 * \brief VBO of the mesh
		 */
		std::unique_ptr<VBO> m_Vbo;

		/**
		 * \brief IBO of the mesh
		 */
		std::unique_ptr<IBO> m_Ibo;

		/**
		 * \brief Name of the mesh
		 * \details This can be used to ask to the resource manager a particular mesh.
		 */
		std::string m_Name;

	public:
		Mesh();

		Mesh(const Mesh& other) = default;

		Mesh& operator=(const Mesh& other) = default;

		/**
		 * \brief Returns a pointer to the VBO of the Mesh.
		 * \return A pointer to the VBO of the Mesh.
		 */
		VBO* GetVbo() const noexcept;

		/**
		 * \brief Returns a pointer to the IBO of the Mesh.
		 * \return A pointer to the IBO of the Mesh.
		 */
		IBO* GetIbo() const noexcept;

		/**
		 * \brief Returns the number of vertices contained in the Mesh.
		 * \return The number of vertices contained in the Mesh.
		 */
		size_t GetVertexCount() const noexcept;

		/**
		 * \brief Returns the number of indices contained in the Mesh.
		 * \return The number of indices contained in the Mesh.
		 */
		size_t GetIndexCount() const noexcept;

		/**
		 * \brief Sets the specified name to the Mesh.
		 * \param name The name to be set.
		 */
		void SetName(const std::string& name) noexcept;

		/**
		 * \brief Returns the name of the Mesh.
		 * \return The name of the Mesh.
		 */
		const std::string& GetName() const noexcept;

		/**
		 * \brief Initializes the buffer objects of the Mesh.
		 * \param primitiveTopology The primitive topology to use for buffer object initialization.
		 */
		void InitiazeBufferObjects(PrimitiveTopology primitiveTopology = PrimitiveTopology::TRIANGLE_LIST) const noexcept;

		/**
		 * \brief Sets the specified array of vertices to the Mesh.
		 * \param vertices The array of vertices to be set.
		 * \param vertexCount The size of the array of vertices to be set.
		 */
		void SetVertexData(const Vertex* vertices, int vertexCount) noexcept;

		/**
		 * \brief Returns a pointer to the Vertex array of the Mesh.
		 * \return A pointer to the Vertex array of the Mesh.
		 */
		Vertex* GetVertexData() const noexcept;

		/**
		 * \brief Adds the specified vertex to the Mesh.
		 * \param vertex The Vertex to be added to the Mesh.
		 */
		void AddVertex(const Vertex& vertex) noexcept;

		/**
		 * \brief Sets the specified array of indices to the Mesh.
		 * \param indices The array of indices to be set.
		 * \param indexCount The size of the array of indices to be set.
		 */
		void SetIndexData(const unsigned int* indices, int indexCount) noexcept;

		/**
		 * \brief Returns a pointer to the index array of the Mesh.
		 * \return A pointer to the index array of the Mesh.
		 */
		unsigned int* GetIndexData() const noexcept;

		/**
		 * \brief Adds the specified index to the Mesh.
		 * \param index The index to be added.
		 */
		void AddIndex(unsigned int index) noexcept;

		/**
		 * \brief Loads a Mesh from the specified file.
		 * \param fileName The file name of the file used to load the Mesh from.
		 * \return TRUE if successful, FALSE otherwise.
		 */
		bool Load(const std::wstring& fileName) noexcept override;

		/**
		 * \brief Generates the indices of the Mesh based on the VertexWinding provided.
		 * \param winding The VertexWinding to be used.
		 */
		void GenerateIndices(VertexWinding winding) noexcept;
	};
}

#endif //BLADE_MESH_H_
