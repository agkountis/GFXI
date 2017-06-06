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
#include "directional_light_component.h"
#include "camera.h"
#include "directional_light.h"
#include "simulation_component.h"
#include "collider_component.h"
#include "bounding_sphere.h"
#include "plane_collider.h"

using namespace Blade;

void GameScene::Initialize()
{
	// Renderable Entity creation ----------------------------------------------------------------------------------------
	//Generate a Sphere.
	Mesh* cube{ MeshUtils::GenerateUvSphere(1.0f, 30, 30, 1.0f, 1.0f) };

	//Register the resource to the manager, so it manages it's lifetime(memory).
	G_ResourceManager.RegisterResource(cube, L"cube");

	//Define a material.
	Material material;
	material.diffuse = Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f };
	material.specular = Vec4f{ 1.0f, 1.0f, 1.0f, 60.0f }; //the w value is the shininess.

	Texture* diffuseTexture{ G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"tunnelDiff5.png") };
	diffuseTexture->SetTextureType(TEX_DIFFUSE);
	material.textures[TEX_DIFFUSE] = diffuseTexture;

	Texture* specularTexture{ G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"tunnelSpec5.png") };
	specularTexture->SetTextureType(TEX_SPECULAR);
	material.textures[TEX_SPECULAR] = specularTexture;

	Texture* normalmapTexture{ G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"tunnelNorm5.png") };
	normalmapTexture->SetTextureType(TEX_NORMAL);
	material.textures[TEX_NORMAL] = normalmapTexture;
	//////////////////////////////////////////////////////////////////////////
	//Create an Entity and a RenderComponent.
	Entity* entity{ new Entity{"TestEntity"} };
	entity->SetPosition(Vec3f{ 0.0f,30.0f,0.0f });
	RenderComponent* rc{ new RenderComponent{entity} };
	rc->SetMesh(cube);
	rc->SetMaterial(material);

	SimulationComponent* simC{ new SimulationComponent{entity,1.0f} };

	ColliderComponent* colC{ new ColliderComponent{entity,std::make_unique<BoundingSphere>(0.5f)} };
	auto cache_entity = entity;
	//Add the entity to the scene so it will get updated.
	AddEntity(entity);

	entity = new Entity{ "Floor" };
	ColliderComponent* colC2{ new ColliderComponent{entity,std::make_unique<PlaneCollider>(Vec3f{0.0f,1.0f,0.0f},0.0f)} };
	AddEntity(entity);
	// -------------------------------------------------------------------------------------------------------------------

	// Camera creation ---------------------------------------------------------------------------------------------------
	//Create an entity and name it Camera1.
	entity = new Entity{ "Camera1" };

	//Since it's going to act as a camera, add a camera component.
	CameraComponent* cc{ new CameraComponent{entity} };

	//Get the window size.
	Vec2i windowSize{ WindowingService::GetWindow(0)->GetSize() };

	CameraDesc cd;
	cd.viewport = Viewport{ Recti{ 0, 0, windowSize }, 0.0f, 1.0f };
	cd.nearPlane = 0.1f;
	cd.farPlane = 500.0f;
	cd.fov = MathUtils::ToRadians(45.0f);

	Camera* cam{ new Camera{ "Camera1", cd } };
	//Set the position of the camera.
	cam->SetPosition(Vec3f{ 0.0f, 0.0f, -50.0f });

	//Add it to the scene.
	AddEntity(cam);

	//Instruct the Camera system to set this camera as the active one.
	G_CameraSystem.SetActiveCamera("Camera1");

	cam = new Camera{ "Camera2", cd };

	cam->SetPosition(Vec3f{ 0.0f, 0.0f, -4.0f });
	cam->SetParent(cache_entity);
	AddEntity(cam);
	// --------------------------------------------------------------------------------------------------------------------

	//Light Creation ------------------------------------------------------------------------------------------------------

	DirectionalLightDesc dlDesc;
	dlDesc.ambientIntensity = Vec4f{ 0.0f, 0.0f, 0.0f, 0.0f };
	dlDesc.diffuseIntensity = Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f };
	dlDesc.specularIntensity = Vec4f{ 1.0f, 1.0f, 1.0f, 60.0f };

	DirectionalLight* dl{ new DirectionalLight{"DirectionalLight1", dlDesc} };

	dl->SetPosition(Vec3f{ 0.0f, 10.0f, 0.0f });

	AddEntity(dl);

	DirectionalLightDesc dlDesc2;
	dlDesc2.ambientIntensity = Vec4f{ 0.0f, 0.0f, 0.0f, 0.0f };
	dlDesc2.diffuseIntensity = Vec4f{ 1.0f, 1.0f, 1.0f, 0.0f };
	dlDesc2.specularIntensity = Vec4f{ 1.0f, 1.0f, 1.0f, 60.0f };

	dl = new DirectionalLight{ "DirectionalLight2", dlDesc2 };

	dl->SetPosition(Vec3f{ 0.0f, -10.0f, 0.0f });

	AddEntity(dl);
	// --------------------------------------------------------------------------------------------------------------------

	// Pipeline Creation --------------------------------------------------------------------------------------------------
	//Allocate and initialize the a render pass pipeline stage.
	GameSceneColorPassStage* colorPassStage{ new GameSceneColorPassStage{ "GameSceneColorPass" } };
	colorPassStage->Initialize();

	//Allocate a render pass pipeline and add the pass to it.
	RenderPassPipeline* pipeline{ new RenderPassPipeline };
	pipeline->AddStage(colorPassStage);

	//Set the pipeline to the render system.
	G_RenderSystem.SetRenderPassPipeline(pipeline);

	// --------------------------------------------------------------------------------------------------------------------
}

void GameScene::OnKeyDown(unsigned char key, int x, int y) noexcept
{
	switch (key)
	{
	case '1':
		G_CameraSystem.SetActiveCamera("Camera1");
		break;
	case '2':
		G_CameraSystem.SetActiveCamera("Camera2");
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
	Entity* cam{ G_CameraSystem.GetActiveCamera()->GetParent() };

	Vec3f currentPos{ cam->GetPosition() };
	//cam->SetPosition(Vec3f{ sin(time / 1000.0f) * 2.0f, currentPos.yz });

	Scene::Update(deltaTime, time);

	G_SimulationSystem.Process(deltaTime);

	G_LightSystem.Process();

	G_BehaviourSystem.Process(deltaTime);
}

void GameScene::Draw() const noexcept
{
	G_RenderSystem.Process();
}
