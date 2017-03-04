#include "game_scene.h"
#include "entity.h"
#include "render_component.h"
#include "mesh_utils.h"
#include "resource_manager.h"
#include "engine_context.h"
#include "game_scene_color_pass.h"
#include "pipeline.h"
#include "d3d/D3D11_texture.h"
#include "windowing_service.h"

using namespace Blade;

void GameScene::Initialize()
{
	// Renderable Entity creation ----------------------------------------------------------------------------------------
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

	//Add the entity to the scene so it will get updated.
	AddEntity(entity);
	// -------------------------------------------------------------------------------------------------------------------

	// Camera creation ---------------------------------------------------------------------------------------------------
	//Create an entity and name it Camera1.
	entity = new Entity{ "Camera1" };

	//Since it's going to act as a camera, add a camera component.
	CameraComponent* cc{ new CameraComponent{entity} };

	//Get the window size.
	Vec2i windowSize{ WindowingService::GetWindow(0)->GetSize() };

	//Create a Rect for the viewport.
	Recti rect{0, 0, windowSize };

	//Set the viewport.
	cc->SetViewport(Viewport{ rect, 0.0f, 1.0f });
	
	//Set the clipping planes.
	cc->SetClippingPlanes(0.1f, 500.0f);

	//Set the FoV.
	cc->SetFov(MathUtils::ToRadians(45.0f));

	//Call the component's Setup method.
	cc->Setup();

	//Set the position of the camera.
	entity->SetPosition(Vec3f{ 0.0f, 0.0f, -10.0f });

	//Add it to the scene.
	AddEntity(entity);

	//Instruct the Camera system to set this camera as the active one.
	EngineContext::GetCameraSystem()->SetActiveCamera("Camera1");

	entity = new Entity{ "Camera2" };
	cc = new CameraComponent{ entity };
	cc->SetViewport(Viewport{ rect, 0.0f, 1.0f });
	cc->SetClippingPlanes(0.1f, 500.0f);
	cc->SetFov(MathUtils::ToRadians(45.0f));
	cc->Setup();
	entity->SetPosition(Vec3f{ 0.0f, 0.0f, -4.0f });

	AddEntity(entity);
	// --------------------------------------------------------------------------------------------------------------------

	// Pipeline Creation --------------------------------------------------------------------------------------------------
	//Allocate and initialize the a render pass pipeline stage.
	GameSceneColorPassStage* colorPassStage{ new GameSceneColorPassStage{ "GameSceneColorPass" } };
	colorPassStage->Initialize();

	//Allocate a render pass pipeline and add the pass to it.
	RenderPassPipeline* pipeline{ new RenderPassPipeline};
	pipeline->AddStage(colorPassStage);

	//Set the pipeline to the render system.
	EngineContext::GetRenderSystem()->SetRenderPassPipeline(pipeline);
	// --------------------------------------------------------------------------------------------------------------------
}

void GameScene::OnKeyDown(unsigned char key, int x, int y) noexcept
{
	switch (key)
	{
	case '1':
		EngineContext::GetCameraSystem()->SetActiveCamera("Camera1");
		break;
	case '2':
		EngineContext::GetCameraSystem()->SetActiveCamera("Camera2");
		break;
	default:
		break;
	}
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
	//Animate the active camera for fun!
	Entity* cam{ EngineContext::GetCameraSystem()->GetActiveCamera()->GetParent() };

	Vec3f currentPos{ cam->GetPosition() };
	cam->SetPosition(Vec3f{ sin(time / 1000.0f) * 2.0f, currentPos.yz });

	Scene::Update(deltaTime, time);
}

void GameScene::Draw() const noexcept
{
	EngineContext::GetRenderSystem()->Process();
}
