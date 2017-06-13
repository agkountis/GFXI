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
#include "collider_component.h"
#include "plane_collider.h"
#include "emitter_component.h"
#include "player_joypad_component.h"
#include "test_behaviour.h"
#include "cannon_weapon_component.h"
#include "other_weapon_component.h"
#include "player.h"
#include <iostream>

#ifdef BLADE_BUILD_OVR
#include "game_scene_color_pass_ovr.h"
#endif

using namespace Blade;

void GameScene::Initialize()
{
	// Renderable Entity creation ----------------------------------------------------------------------------------------
	//Generate a Sphere.
	Mesh* cube{ MeshUtils::GenerateUvSphere(1.0f, 30, 30, 1.0f, 1.0f) };
	//Register the resource to the manager, so it manages it's lifetime(memory).
	G_ResourceManager.RegisterResource(cube, L"cube");

	Mesh* plane{ MeshUtils::GeneratePlaneXy(1.0f) };
	G_ResourceManager.RegisterResource(plane, L"plane");

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

	Entity* arena{ new Entity{ "arena" } };
	arena->Load(L"data/models/arena5.fbx");
	AddEntity(arena);

	Entity* entity{ new Entity{ "Environment" } };
	ColliderComponent* floor{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ 0.0f,1.0f,0.0f },0.0f) } };
	ColliderComponent* wall1{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ -1.0f,0.0f,0.0f },-40.0f) } };
	ColliderComponent* wall2{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ 1.0f,0.0f,0.0f },-40.0f) } };
	ColliderComponent* wall3{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ 0.0f,0.0f,1.0f },-40.0f) } };
	ColliderComponent* wall4{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ 0.0f,0.0f,-1.0f },-40.0f) } };
	AddEntity(entity);


	auto p{ m_PlayerFactory.CreateLocalKeyboardPlayer("player1",L"player1.fbx") };
	AddEntity(p);

	auto p2{ m_PlayerFactory.CreateLocalJoypadPlayer("player2",L"player1.fbx") };
	AddEntity(p2);

	auto weapon1{ m_WeaponFactory.CreateWeapon1("weapon1") };
	AddEntity(weapon1);

	auto weapon2{ m_WeaponFactory.CreateWeapon2("weapon2") };
	AddEntity(weapon2);



	// Camera creation ---------------------------------------------------------------------------------------------------
	//Get the window size.
	Vec2i windowSize{ WindowingService::GetWindow(0)->GetSize() };

	CameraDesc cd;
	cd.viewport = Viewport{ Recti{ 0, 0, windowSize }, 0.0f, 1.0f };
	cd.nearPlane = 0.1f;
	cd.farPlane = 500.0f;
	cd.fov = MathUtils::ToRadians(45.0f);

	Camera* cam{ new Camera{ "Camera1", cd } };
	//Set the position of the camera.
	cam->SetPosition(Vec3f{ -5.0f, 1.0f, -8.0f });
	cam->SetOrientation(Vec3f{ 0.0f, 1.0f, 0.0f }, MathUtils::ToRadians(-20.0f));

	//Add it to the scene.
	AddEntity(cam);

	cam = new Camera{ "Camera2", cd };
	cam->SetPosition(Vec3f{ 0.0f, 5.0f, -20.0f });
	AddEntity(cam);
	cam->SetParent(p2);

	cam = new Camera{ "Camera3", cd };
	cam->SetPosition(Vec3f{ 0.0f, 10.0f, -50.0f });
	AddEntity(cam);


	cam = new Camera{ "Camera4", cd };

	cam->SetPosition(Vec3f{ 0.0f, 0.0f, -4.0f });
	cam->SetParent(p2);
	AddEntity(cam);

	//Instruct the Camera system to set this camera as the active one.
	G_CameraSystem.SetActiveCamera("Camera3");

	//Instruct the Camera system to set this camera as the active one.
	G_CameraSystem.SetActiveCamera("Camera3");

	// --------------------------------------------------------------------------------------------------------------------

	//Light Creation ------------------------------------------------------------------------------------------------------

	DirectionalLightDesc dlDesc;
	dlDesc.ambientIntensity = Vec4f{ 0.0f, 0.0f, 0.0f, 0.0f };
	dlDesc.diffuseIntensity = Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f };
	dlDesc.specularIntensity = Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f };

	DirectionalLight* dl{ new DirectionalLight{"DirectionalLight1", dlDesc} };

	dl->SetPosition(Vec3f{ 0.0f, 10.0f, -3.0f });

	AddEntity(dl);

	DirectionalLightDesc dlDesc2;
	dlDesc2.ambientIntensity = Vec4f{ 0.0f, 0.0f, 0.0f, 0.0f };
	dlDesc2.diffuseIntensity = Vec4f{ 1.0f, 1.0f, 1.0f, 0.0f };
	dlDesc2.specularIntensity = Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f };

	dl = new DirectionalLight{ "DirectionalLight2", dlDesc2 };

	dl->SetPosition(Vec3f{ 0.0f, -10.0f, 0.0f });

	AddEntity(dl);
	// --------------------------------------------------------------------------------------------------------------------

	// Pipeline Creation --------------------------------------------------------------------------------------------------
	//Allocate a render pass pipeline.
	RenderPassPipeline* pipeline{ new RenderPassPipeline };

#ifdef BLADE_BUILD_OVR
	GameSceneColorPassStageOvr* ovrStage{ new GameSceneColorPassStageOvr{ " ovrPass " } };
	ovrStage->Initialize();
	pipeline->AddStage(ovrStage);
#else
	//Allocate and initialize the a render pass pipeline stage.
	GameSceneColorPassStage* colorPassStage{ new GameSceneColorPassStage{ "GameSceneColorPass" } };
	colorPassStage->Initialize();
	pipeline->AddStage(colorPassStage);
#endif

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
	case '3':
		G_CameraSystem.SetActiveCamera("Camera3");
		break;
	case '4':
		G_CameraSystem.SetActiveCamera("Camera4");
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
	Scene::Update(deltaTime, time);

	G_InputManager.Update(deltaTime);

	G_SimulationSystem.Process(deltaTime);

	G_LightSystem.Process();

	G_BehaviourSystem.Process(deltaTime, time);

}

void GameScene::Draw() const noexcept
{
	G_RenderSystem.Process();
}
