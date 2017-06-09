#ifndef ASSIMP_UTILS_H_
#define ASSIMP_UTILS_H_
#include "types.h"
#include "assimp/scene.h"
#include "mesh.h"
#include "material.h"

namespace Blade {
	class Entity;
}

namespace AssimpUtils
{
	Blade::Vec2f AssToBlade(const aiVector2D& v) noexcept;

	Blade::Vec3f AssToBlade(const aiVector3D& v) noexcept;

	Blade::Vec4f AssToBlade(const aiColor4D& c) noexcept;

	Blade::Quatf AssToBlade(const aiQuaternion& q) noexcept;

	Blade::Mat4f AssToBlade(const aiMatrix4x4& m) noexcept;

	long AssToBlade(const aiAnimation* aiAnim, double aiTime) noexcept;

	Blade::Entity* LoadAssNode(const aiScene* aiScene, const aiNode* aiNode) noexcept;

	Blade::Mesh* LoadAssMesh(const aiMesh* aiMesh) noexcept;

	Blade::Material LoadAssMaterial(const aiMaterial* aiMaterial) noexcept;

	bool LoadEntity(const std::wstring& fileName, Blade::Entity* thisObject) noexcept;

	//TODO: Implement animation loading and animation engine structure.
}

#endif //ASSIMP_UTILS_H_
