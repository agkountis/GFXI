#ifndef BLADE_MESH_UTILS_H_
#define BLADE_MESH_UTILS_H_
#include "mesh.h"

namespace Blade
{
	namespace MeshUtils
	{
		Mesh* GenerateCube(float size, VertexWinding vertexWinding = VertexWinding::CLOCKWISE) noexcept;

		Mesh* GenerateUvSphere(float radius, int slices, int stacks, float urange = 1.0f, float vrange = 1.0f) noexcept;

		Mesh* GeneratePlaneXy(float size) noexcept;

		void FlipNormals(const Mesh* m) noexcept;
	}
}

#endif //BLADE_MESH_UTILS_H_
