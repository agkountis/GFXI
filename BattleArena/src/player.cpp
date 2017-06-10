#include "..\include\player.h"
#include "engine_context.h"


Player::Player(const std::string& name,bool local):
	Blade::Entity(name), 
	m_Local{local}
{
	this->SetPosition(Blade::Vec3f{ 1.0f, 25.0f,0.0f });
	Blade::RenderComponent* rc3{ new Blade::RenderComponent{this} };
	Blade::Mesh* cube{ Blade::MeshUtils::GenerateCube(4,VertexWinding::CLOCKWISE) };//GenerateUvSphere(1.0f, 30, 30, 1.0f, 1.0f) };
	Blade::G_ResourceManager.RegisterResource(cube, L"plxxx");
	rc3->SetMesh(cube);


	//Define a material.
	Blade::Material material;
	material.diffuse = Blade::Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f };
	material.specular = Blade::Vec4f{ 1.0f, 1.0f, 1.0f, 60.0f }; //the w value is the shininess.
	
	Blade::Texture* diffuseTexture{ Blade::G_ResourceManager.Get<Blade::D3D11Texture>(Blade::TEXTURE_PATH + L"tunnelDiff5.png") };
	diffuseTexture->SetTextureType(Blade::TEX_DIFFUSE);
	material.textures[Blade::TEX_DIFFUSE] = diffuseTexture;

	Blade::Texture* specularTexture{ Blade::G_ResourceManager.Get<Blade::D3D11Texture>(Blade::TEXTURE_PATH + L"tunnelSpec5.png") };
	specularTexture->SetTextureType(Blade::TEX_SPECULAR);
	material.textures[Blade::TEX_SPECULAR] = specularTexture;

	Blade::Texture* normalmapTexture{ Blade::G_ResourceManager.Get<Blade::D3D11Texture>(Blade::TEXTURE_PATH + L"tunnelNorm5.png") };
	normalmapTexture->SetTextureType(Blade::TEX_NORMAL);

	rc3->SetMaterial(material);
	if (local)
	{
		Blade::SimulationComponent* simC3{ new Blade::SimulationComponent{ this,1.0f } };
	}
	Blade::ColliderComponent* colC3{ new Blade::ColliderComponent{ this,std::make_unique<Blade::BoundingSphere>(1.0f) } };
}


Player::~Player()
{
}
