#include "assimp_utils.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "trace.h"
#include "entity.h"
#include <locale>
#include <codecvt>
#include "render_component.h"
#include "engine_context.h"
#include "d3d/D3D11_texture.h"
#include <sstream>
#include "bounding_sphere.h"

using namespace Blade;

static unsigned int s_MeshCount{ 0 };

namespace AssimpUtils
{
	static std::string ToString(const std::wstring& wstring)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

		return converter.to_bytes(wstring);
	}

	static std::wstring ToWstring(const std::string& string)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

		return converter.from_bytes(string);
	}

	Vec2f AssToBlade(const aiVector2D& v) noexcept
	{
		return Vec2f{ v.x, v.y };
	}

	Vec3f AssToBlade(const aiVector3D& v) noexcept
	{
		return Vec3f{ v.x, v.y, v.z };
	}

	Vec4f AssToBlade(const aiColor4D& c) noexcept
	{
		return Vec4f{ c.r, c.g, c.b, c.a };
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

	Mesh* LoadAssMesh(const aiMesh* aiMesh) noexcept
	{
		Mesh* m{ new Mesh };

		m->SetName(aiMesh->mName.data);

		if (m->GetName().empty())
		{
			m->SetName("Mesh" + std::to_string(s_MeshCount++));
		}

		if (aiMesh->HasPositions())
		{
			std::vector<Vertex> vertices;
			vertices.resize(aiMesh->mNumVertices);

			for (int i = 0; i < aiMesh->mNumVertices; ++i)
			{
				vertices[i].position = glm::vec3{ aiMesh->mVertices[i].x, aiMesh->mVertices[i].y, aiMesh->mVertices[i].z };
				vertices[i].normal = glm::vec3{ aiMesh->mNormals[i].x, aiMesh->mNormals[i].y, aiMesh->mNormals[i].z };
				vertices[i].tangent = glm::vec3{ aiMesh->mTangents[i].x, aiMesh->mTangents[i].y, aiMesh->mTangents[i].z };
				vertices[i].texcoord = glm::vec2{ aiMesh->mTextureCoords[0][i].x, aiMesh->mTextureCoords[0][i].y };
			}

			m->SetVertexData(vertices.data(), vertices.size());
		}
		else
		{
			delete m;
			return nullptr;
		}

		if (aiMesh->HasFaces())
		{
			std::vector<unsigned int> indices;

			for (int i = 0; i < aiMesh->mNumFaces; ++i)
			{
				const aiFace& Face = aiMesh->mFaces[i];
				assert(Face.mNumIndices == 3);
				indices.push_back(Face.mIndices[0]);
				indices.push_back(Face.mIndices[1]);
				indices.push_back(Face.mIndices[2]);
			}

			m->SetIndexData(indices.data(), indices.size());
		}

		m->InitiazeBufferObjects();

		G_ResourceManager.RegisterResource(m, ToWstring(m->GetName()));

		return m;
	}

	std::wstring GetTextureFileName(const std::wstring& path) noexcept
	{
		std::wcout << path << std::endl;

		return L"";
	}

	Material LoadAssMaterial(const aiMaterial* aiMaterial) noexcept
	{
		Material mat;

		aiColor4D col;

		aiGetMaterialColor(aiMaterial, AI_MATKEY_COLOR_DIFFUSE, &col);

		mat.diffuse = AssToBlade(col);

		float alpha{ 1.0f };
		aiGetMaterialFloat(aiMaterial, AI_MATKEY_OPACITY, &alpha);

		mat.diffuse.a = alpha;

		if (alpha < 1.0f)
		{
			mat.blendState = RenderStateType::BS_BLEND_ALPHA;
		}

		float glossiness{ 60 };
		aiGetMaterialFloat(aiMaterial, AI_MATKEY_SHININESS, &glossiness);

		float t = log2(glossiness) / 10.0f;

		float shininess = MathUtils::Lerp(1.0f, 128.0f, t);

		mat.specular = Vec4f{1.0f, 1.0f, 1.0f, shininess};

		aiUVTransform uvTransform;
		aiGetMaterialUVTransform(aiMaterial, AI_MATKEY_UVTRANSFORM_DIFFUSE(0), &uvTransform);

		mat.textureMatrix = MathUtils::Translate(mat.textureMatrix, Vec3f{ AssToBlade(uvTransform.mTranslation), 0.0f });
		mat.textureMatrix = MathUtils::Scale(mat.textureMatrix, Vec3f{ AssToBlade(uvTransform.mScaling), 1.0f });

		aiString str;

		if (aiMaterial->GetTextureCount(aiTextureType_DIFFUSE))
		{
			// support only 1 diffuse texture for now.
			aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &str);

			mat.textures[TEX_DIFFUSE] = G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + ToWstring(str.data));

			if (mat.textures[TEX_DIFFUSE])
			{
				mat.textures[TEX_DIFFUSE]->SetTextureType(TEX_DIFFUSE);
			}
			else
			{
				BLADE_WARNING("Mesh does not have a diffuse texture.");
			}
		}

		if (aiMaterial->GetTextureCount(aiTextureType_SPECULAR))
		{
			// support only 1 specular texture for now.
			aiMaterial->GetTexture(aiTextureType_SPECULAR, 0, &str);

			mat.textures[TEX_SPECULAR] = G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + ToWstring(str.data));

			if (mat.textures[TEX_SPECULAR])
			{
				mat.textures[TEX_SPECULAR]->SetTextureType(TEX_SPECULAR);
			}
			else
			{
				BLADE_WARNING("Mesh does not have a specular texture.");
			}
		}

		if (aiMaterial->GetTextureCount(aiTextureType_NORMALS))
		{
			// support only 1 normal-map texture for now.
			aiMaterial->GetTexture(aiTextureType_NORMALS, 0, &str);

			mat.textures[TEX_NORMAL] = G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + ToWstring(str.data));

			if (mat.textures[TEX_NORMAL])
			{
				mat.textures[TEX_NORMAL]->SetTextureType(TEX_NORMAL);
			}
			else
			{
				BLADE_WARNING("Mesh does not have a normal-map texture.");
			}
		}

		return mat;
	}

	static void Split(const std::string& s, char delim, std::vector<std::string>& elems)
	{
		std::stringstream ss{ s };

		std::string item;

		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
	}

	Entity* LoadAssNode(const aiScene* aiScene, const aiNode* aiNode) noexcept
	{
		std::string name{ aiNode->mName.C_Str() };
		Entity* entity{ new Entity{ name } };

		std::vector<std::string> splitString;
		Split(name, '_', splitString);

		if (splitString[0] == "COL")
		{
			if (splitString[1] == "SPHERE")
			{
				std::stringstream s{ splitString[2] };

				float radius;
				s >> radius;
				//ColliderComponent* cc{ new ColliderComponent{entity, std::make_unique<BoundingSphere>(radius)} };
			}
		}

		// Mesh and Material loading
		unsigned int meshCount{ aiNode->mNumMeshes };
		if (meshCount)
		{
			if (meshCount > 1)
			{
				BLADE_WARNING("Node has more than 1 meshes. Feature not supported. Using the 1st mesh only.");
			}

			RenderComponent* rc{ new RenderComponent{ entity } };

			aiMesh* aiMesh{ aiScene->mMeshes[aiNode->mMeshes[0]] };

			Mesh* mesh{ LoadAssMesh(aiMesh) };

			rc->SetMesh(mesh);

			aiMaterial* aiMat{ aiScene->mMaterials[aiMesh->mMaterialIndex] };

			Material mat = LoadAssMaterial(aiMat);

			rc->SetMaterial(mat);
		}

		// Node transformation loading
		aiVector3D aiPosition;
		aiQuaternion aiOrientation;
		aiVector3D aiScaling;

		aiNode->mTransformation.Decompose(aiScaling, aiOrientation, aiPosition);

		entity->SetPosition(AssToBlade(aiPosition));
		entity->SetOrientation(AssToBlade(aiOrientation));
		entity->SetScale(AssToBlade(aiScaling));


		// recursion for all the children
		for (int i = 0; i < aiNode->mNumChildren; ++i)
		{
			Entity* child{ LoadAssNode(aiScene, aiNode->mChildren[i]) };

			entity->AddChild(child);
		}

		return entity;
	}


	bool LoadEntity(const std::wstring& fileName, Entity* thisObject) noexcept
	{
		unsigned int postProcessFlags{ aiProcess_CalcTangentSpace |
			aiProcess_GenSmoothNormals |
			aiProcess_Triangulate |
			aiProcess_ConvertToLeftHanded |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType };

		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

		std::string res{ ToString(fileName) };

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

				Entity* entity{ LoadAssNode(scene, child) };

				thisObject->AddChild(entity);
			}
		}
		else
		{
			BLADE_ERROR("The scene has no root node.");
			return false;
		}

		aiReleaseImport(scene);

		return true;
	}
}
