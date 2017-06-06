#ifndef ASSIMP_UTILS_H_
#define ASSIMP_UTILS_H_
#include "types.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "mesh.h"

namespace Blade {
	class Entity;
}

namespace AssimpUtils
{
	Blade::Vec3f AssToBlade(const aiVector3D &v) noexcept;

	Blade::Quatf AssToBlade(const aiQuaternion& q) noexcept;

	Blade::Mat4f AssToBlade(const aiMatrix4x4& m) noexcept;

	long AssToBlade(const aiAnimation* aiAnim, double aiTime) noexcept;

	Blade::Entity* LoadAssNode(const aiScene* scene, const aiNode* node) noexcept;

	Blade::Mesh* LoadAssMesh(const aiMesh* mesh) noexcept;

	bool LoadEntity(const std::wstring& fileName, Blade::Entity* thisObject) noexcept;
}

#endif //ASSIMP_UTILS_H_
