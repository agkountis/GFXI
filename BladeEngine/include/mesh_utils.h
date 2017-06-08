#ifndef BLADE_MESH_UTILS_H_
#define BLADE_MESH_UTILS_H_
#include "mesh.h"

namespace Blade
{
	namespace MeshUtils
	{
		/*
		\brief Generate a cube mesh.
		*/
		Mesh* GenerateCube(float size, VertexWinding vertexWinding = VertexWinding::CLOCKWISE) noexcept;

		/*
		\brief Generate a sphere mesh
		*/
		Mesh* GenerateUvSphere(float radius, int slices, int stacks, float urange = 1.0f, float vrange = 1.0f) noexcept;

		/*
		\brief Generate a plane
		*/
		Mesh* GeneratePlaneXy(float size) noexcept;

		/*
		\brief Flip the normals of one mesh
		*/
		void FlipNormals(const Mesh* m) noexcept;
	}
}

#endif //BLADE_MESH_UTILS_H_
