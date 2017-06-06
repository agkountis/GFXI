#include "assimp_utils.h"
#include "trace.h"
#include "entity.h"
#include <locale>
#include <codecvt>
#include "render_component.h"

using namespace Blade;

namespace AssimpUtils
{
	Vec3f AssToBlade(const aiVector3D& v) noexcept
	{
		return Vec3f{ v.x, v.y, v.z };
	}

	Quatf AssToBlade(const aiQuaternion& q) noexcept
	{
		return Quatf{ q.w, q.x, q.y, q.z };
	}

	Mat4f AssToBlade(const aiMatrix4x4& m) noexcept
	{
		Mat4f mat;
		memcpy(&mat[0], &m, 16 * sizeof(float));
		return mat;
	}

	long AssToBlade(const aiAnimation* aiAnim, double aiTime) noexcept
	{
		double sec;

		if (aiAnim->mTicksPerSecond < 1e-6) //assume time is in frames.
		{
			sec = aiTime / 30.0;
		}
		else
		{
			sec = aiTime / aiAnim->mTicksPerSecond;
		}

		if (aiTime < 0)
		{
			BLADE_WARNING("negative keyframe timestamp.");
		}

#undef max
		if (aiTime > std::numeric_limits<double>::max())
		{
			BLADE_WARNING("very big keyframe timestamp");
		}

		return sec * 1000.0;
	}

	Mesh* LoadAssMesh(const aiMesh* mesh) noexcept
	{
		Mesh* m{ new Mesh };

		//DO MESH LOADING.

		return m;
	}

	Entity* LoadAssNode(const aiScene* scene, const aiNode* node) noexcept
	{
		Entity* entity{ new Entity{ node->mName.C_Str() } };

		unsigned int meshCount{ node->mNumMeshes };
		if (meshCount)
		{
			if (meshCount > 1)
			{
				BLADE_WARNING("Node has more than 1 meshes. Feature not supported. Using the 1st mesh only.");
			}

			RenderComponent* rc{ new RenderComponent{entity} };

			//LOAD MESH
		}


		return entity;
	}
	

	bool LoadEntity(const std::wstring& fileName, Entity* thisObject) noexcept
	{
		unsigned int postProcessFlags{ aiProcess_GenSmoothNormals | aiProcess_Triangulate
			| aiProcess_CalcTangentSpace | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices };

		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

		std::string res = converter.to_bytes(fileName);

		const aiScene* scene{ aiImportFile(res.c_str(), postProcessFlags) };

		if (!scene)
		{
			BLADE_ERROR("Failed to load scene: " + res);
			return false;
		}

		aiNode* rootNode{ scene->mRootNode };
		if (rootNode)
		{
			for (int i = 0; i < rootNode->mNumChildren; ++i)
			{
				aiNode* child{ rootNode->mChildren[i] };

			}
		}
		else
		{
			BLADE_ERROR("The scene has no root node.");
			return false;
		}

		return true;
	}
}
