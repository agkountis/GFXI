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
#include "emitter_component.h"
#include "player_joypad_component.h"
#include "player_keyboard_component.h"
#include "test_behaviour.h"
#include "cannon_weapon_component.h"
#include "other_weapon_component.h"
#include "game_scene_color_pass_ovr.h"


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
	arena->Load(L"data/models/arena4.fbx");
	AddEntity(arena);

	Entity* entity{ new Entity{ "Environment" } };
	ColliderComponent* floor{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ 0.0f,1.0f,0.0f },0.0f) } };
	ColliderComponent* wall1{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ -1.0f,0.0f,0.0f },-40.0f) } };
	ColliderComponent* wall2{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ 1.0f,0.0f,0.0f },-40.0f) } };
	ColliderComponent* wall3{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ 0.0f,0.0f,1.0f },-40.0f) } };
	ColliderComponent* wall4{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ 0.0f,0.0f,-1.0f },-40.0f) } };
	AddEntity(entity);

	//First ball
	entity = new Entity{ "Ball" };
	entity->SetPosition(Vec3f{ 0.0f, 80.0f,-1.0f });
	RenderComponent* rc{ new RenderComponent{entity} };
	rc->SetMesh(cube);
	rc->SetMaterial(material);
	SimulationComponent* simC{ new SimulationComponent{entity,1.0f} };
	ColliderComponent* colC{ new ColliderComponent{entity,std::make_unique<BoundingSphere>(1.0f)} };
	TestBehaviour* tb{ new TestBehaviour(entity) };
	colC->SetListener(tb);

	auto cache_entity = entity;
	/*
	EmitterComponent* ec = new EmitterComponent{ entity };
	ec->SetLifeSpan(1.0f);
	ec->SetMaxParticles(1000);
	ec->SetSpawnRate(200);
	ec->SetActive(true);
	ec->SetParticleSize(3.f);
	ec->SetSpawnRadius(1.5f);
	ec->SetVelocity(Vec3f{ 0.0f, 1.0f, 0.0f });
	ec->SetVelocityRange(1.3f);
	ec->SetExternalForce(Vec3f{ 0.0f, -1.3f, 0.0f });
	ec->SetMesh(G_ResourceManager.Get<Mesh>(L"plane"));
	ec->SetStartColor(Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f });
	ec->SetEndColor(Vec4f{ 1.0f, 1.0f, 1.0f, 0.1f });
	ec->SetBlendStateType(RenderStateType::BS_BLEND_ADDITIVE);
	Texture* tex{ G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"expl02.png") };
	tex->SetTextureType(TEX_DIFFUSE);
	ec->SetTexture(tex);
	*/


	PlayerJoypadComponent* tjc{ new PlayerJoypadComponent{ entity,Blade::JoypadNumber::JOYPAD1 } };
	tjc->Setup();

	//PlayerKeyboardComponent* pkc{ new PlayerKeyboardComponent{entity} };
	//pkc->Setup();


	CannonWeaponComponent* cwc{ new CannonWeaponComponent{entity,WeaponPosition::LEFT} };
	OtherWeaponComponent* owc{ new OtherWeaponComponent{entity,WeaponPosition::RIGHT} };

	AddEntity(entity);

	//Second ball
	entity = new Entity{ "Ball2" };
	entity->SetPosition(Vec3f{ 1.0f, 85.0f,0.0f });
	RenderComponent* rc3 {new RenderComponent{ entity } };
	rc3->SetMesh(cube);
	rc3->SetMaterial(material);
	SimulationComponent* simC3{ new SimulationComponent{ entity,1.0f } };
	ColliderComponent* colC3{ new ColliderComponent{ entity,std::make_unique<BoundingSphere>(1.0f) } };


	PlayerJoypadComponent* tjc2{ new PlayerJoypadComponent{ entity,Blade::JoypadNumber::JOYPAD2 } };
	tjc2->Setup();


	AddEntity(entity);

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

	cam->SetPosition(Vec3f{ 0.0f, 14.0f, -11.0f });
	cam->SetOrientation(Vec3f{ 1.0, 0.0, 0.0 }, MathUtils::ToRadians(32.0f));
	AddEntity(cam);

	cam = new Camera{ "Camera3", cd };

	cam->SetPosition(Vec3f{ 0.0f, 10.0f, -50.0f });
	AddEntity(cam);

	cam = new Camera{ "Camera4", cd };

	cam->SetPosition(Vec3f{ 0.0f, 0.0f, -4.0f });
	cam->SetParent(cache_entity);
	AddEntity(cam);

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
	G_InputManager.Update(deltaTime);

	Scene::Update(deltaTime, time);

	G_SimulationSystem.Process(deltaTime);

	G_LightSystem.Process();

	G_BehaviourSystem.Process(deltaTime, time);

}

void GameScene::Draw() const noexcept
{
	G_RenderSystem.Process();
}
