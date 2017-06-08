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

	Entity* entity{ new Entity{ "Environment" } };
	ColliderComponent* floor{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ 0.0f,1.0f,0.0f },0.0f) } };
	ColliderComponent* wall1{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ -1.0f,0.0f,0.0f },-10.0f) } };
	ColliderComponent* wall2{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ 1.0f,0.0f,0.0f },-10.0f) } };
	ColliderComponent* wall3{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ 0.0f,0.0f,1.0f },-10.0f) } };
	ColliderComponent* wall4{ new ColliderComponent{ entity,std::make_unique<PlaneCollider>(Vec3f{ 0.0f,0.0f,-1.0f },-10.0f) } };
	AddEntity(entity);

	//First ball
	entity = new Entity{"Ball"};
	entity->SetPosition(Vec3f{ 0.0f,50.0f,-1.0f });
	RenderComponent* rc{ new RenderComponent{entity} };
	rc->SetMesh(cube);
	rc->SetMaterial(material);
	SimulationComponent* simC{ new SimulationComponent{entity,1.0f} };
	ColliderComponent* colC{ new ColliderComponent{entity,std::make_unique<BoundingSphere>(1.0f)} };
	auto cache_entity = entity;
	AddEntity(entity);

	//Second ball
	entity = new Entity{ "Ball2" };
	entity->SetPosition(Vec3f{ 1.0f,55.0f,0.0f });
	RenderComponent* rc3 {new RenderComponent{ entity } };
	rc3->SetMesh(cube);
	rc3->SetMaterial(material);
	SimulationComponent* simC3{ new SimulationComponent{ entity,1.0f } };
	ColliderComponent* colC3{ new ColliderComponent{ entity,std::make_unique<BoundingSphere>(1.0f) } };
	AddEntity(entity);

	Entity* arena{ new Entity{"arena"} };
	arena->Load(L"data\\models\\arena3.fbx");
	AddEntity(arena);

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
	//Allocate and initialize the a render pass pipeline stage.
	GameSceneColorPassStage* colorPassStage{ new GameSceneColorPassStage{ "GameSceneColorPass" } };
	colorPassStage->Initialize();

	//Allocate a render pass pipeline and add the pass to it.
	RenderPassPipeline* pipeline{ new RenderPassPipeline };
	pipeline->AddStage(colorPassStage);

	//Set the pipeline to the render system.
	G_RenderSystem.SetRenderPassPipeline(pipeline);

	// --------------------------------------------------------------------------------------------------------------------

	if (!G_InputManager.AssignDeviceToPlayer(Player::PLAYER1, 0)) {
		BLADE_TRACE("Could not assign device 0 to player 1");
	}
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

	if (G_InputManager.GetActiveDevice(Player::PLAYER1) != nullptr)
	{
		InputState p1State{};
		p1State = G_InputManager.GetActiveDevice(Player::PLAYER1)->GetInputState();

		bool buttons[8];
		buttons[0] = (p1State.digitalButtonData & JOYBTN_FACE1);
		buttons[1] = (p1State.digitalButtonData & JOYBTN_FACE2);
		buttons[2] = (p1State.digitalButtonData & JOYBTN_FACE3);
		buttons[3] = (p1State.digitalButtonData & JOYBTN_FACE4);
		buttons[4] = (p1State.digitalButtonData & JOYBTN_SHOULDER1);
		buttons[5] = (p1State.digitalButtonData & JOYBTN_SHOULDER2);
		buttons[6] = (p1State.digitalButtonData & JOYBTN_OPTION1);
		buttons[7] = (p1State.digitalButtonData & JOYBTN_OPTION2);

		BLADE_TRACE(
			"A=[" << (int)((buttons[0])? 1 : 0) << "] " <<
			"B=[" << (int)((buttons[1]) ? 1 : 0) << "] " <<
			"X=[" << (int)((buttons[2]) ? 1 : 0) << "] " <<
			"Y=[" << (int)((buttons[3]) ? 1 : 0) << "] " <<
			"LB=[" << (int)((buttons[4]) ? 1 : 0) << "] " <<
			"RB=[" << (int)((buttons[5]) ? 1 : 0) << "] " <<
			"ST=[" << (int)((buttons[6]) ? 1 : 0) << "] " <<
			"BK=[" << (int)((buttons[7]) ? 1 : 0) << "] "
		);

	}


	G_SimulationSystem.Process(deltaTime);

	G_LightSystem.Process();

	G_BehaviourSystem.Process(deltaTime);
}

void GameScene::Draw() const noexcept
{
	G_RenderSystem.Process();
}
