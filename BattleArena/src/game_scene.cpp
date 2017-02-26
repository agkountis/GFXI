#include "game_scene.h"
#include "entity.h"
#include "render_component.h"
#include "mesh_utils.h"
#include "resource_manager.h"
#include "engine_context.h"
#include "game_scene_color_pass.h"
#include "pipeline.h"
#include "d3d/D3D11_texture.h"

using namespace Blade;

void GameScene::Initialize()
{
	//Generate a Sphere.
	Mesh* cube{ MeshUtils::GenerateUvSphere(1.0f, 30, 30, 1.0f, 1.0f) };

	//Register the resource to the manager, so it manages it's lifetime(memory).
	ResourceManager::RegisterResource(cube, L"cube");

	//Define a material.
	Material material;
	material.diffuse = Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f };
	material.specular = Vec4f{ 1.0f, 1.0f, 1.0f, 60.0f }; //the w value is the shininess.

	Texture* diffuseTexture{ ResourceManager::Get<D3D11Texture>(TEXTURE_PATH + L"tunnelDiff5.png") };
	diffuseTexture->SetTextureType(TEX_DIFFUSE);
	material.textures[TEX_DIFFUSE] = diffuseTexture;

	Texture* specularTexture{ ResourceManager::Get<D3D11Texture>(TEXTURE_PATH + L"tunnelSpec5.png") };
	specularTexture->SetTextureType(TEX_SPECULAR);
	material.textures[TEX_SPECULAR] = specularTexture;

	Texture* normalmapTexture{ ResourceManager::Get<D3D11Texture>(TEXTURE_PATH + L"tunnelNorm5.png") };
	normalmapTexture->SetTextureType(TEX_NORMAL);
	material.textures[TEX_NORMAL] = normalmapTexture;

	//Create an Entity and a RenderComponent.
	Entity* entity{ new Entity{"TestEntity"} };
	RenderComponent* rc{ new RenderComponent{entity} };
	rc->SetMesh(cube);
	rc->SetMaterial(material);
	rc->Setup();

	//Add the entity to the scene so it will get updated.
	AddEntity(entity);

	//Allocate and initialize the a render pass pipeline stage.
	GameSceneColorPassStage* colorPassStage{ new GameSceneColorPassStage{ "GameSceneColorPass" } };
	colorPassStage->Initialize();

	//Allocate a render pass pipeline and add the pass to it.
	RenderPassPipeline* pipeline{ new RenderPassPipeline};
	pipeline->AddStage(colorPassStage);

	//Set the pipeline to the render system.
	EngineContext::GetRenderSystem()->SetRenderPassPipeline(pipeline);
}

void GameScene::OnKeyDown(unsigned char key, int x, int y) noexcept
{
}

void GameScene::OnKeyUp(unsigned char key, int x, int y) noexcept
{
}

void GameScene::OnMouseMotion(int x, int y) noexcept
{
}

void GameScene::OnMouseClick(int button, bool state, int x, int y) noexcept
{
}

void GameScene::Update(float deltaTime, long time) noexcept
{
	Scene::Update(deltaTime, time);
}

void GameScene::Draw() const noexcept
{
	EngineContext::GetRenderSystem()->Process();
}
