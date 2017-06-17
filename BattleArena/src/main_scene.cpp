#include "main_scene.h"
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
#include "other_weapon_component.h"
#include "player.h"
#include "explosion.h"
#include <iostream>
#include "resource_utils.h"
#include "resource_manager.h"
#include "mesh_utils.h"
#include "engine_context.h"
#include "game_scene_color_pass.h"

#ifdef BLADE_BUILD_OVR
#include "game_scene_color_pass_ovr.h"
#endif


using namespace Blade;
using namespace ResourceUtils;

bool MainScene::Initialize()
{
	// Renderable Entity creation ----------------------------------------------------------------------------------------
	//Generate a Sphere.
	Mesh* cube{ MeshUtils::GenerateUvSphere(1.0f, 30, 30, 1.0f, 1.0f) };
	//Register the resource to the manager, so it manages it's lifetime(memory).
	G_ResourceManager.RegisterResource(cube, L"cube");

	Mesh* plane{ MeshUtils::GeneratePlaneXy(1.0f) };
	G_ResourceManager.RegisterResource(plane, L"plane");

	Texture* tex = G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"star.jpg");

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
	arena->Load(L"data/models/main_menu.fbx");
	AddEntity(arena);

	//////////////////////////////////////////////////////////////////////////
	Vec2i windowSize{ WindowingService::GetWindow(0)->GetSize() };
	CameraDesc cd;
	cd.viewport = Viewport{ Recti{ 0, 0, windowSize }, 0.0f, 1.0f };
	cd.nearPlane = 0.1f;
	cd.farPlane = 500.0f;
	cd.fov = MathUtils::ToRadians(45.0f);

	//Set the position of the camera.
	Camera* cam{ new Camera{ "Camera1", cd } };
	cam->SetPosition(Vec3f{ 0.0f, 5.23423f, -25.0f });
	//cam->SetOrientation(Vec3f{ 1.0f, 0.0f, 0.0f }, MathUtils::ToRadians(40.0f));
	AddEntity(cam);
	G_CameraSystem.SetActiveCamera("Camera1");
	// --------------------------------------------------------------------------------------------------------------------

	//Light Creation ------------------------------------------------------------------------------------------------------

	DirectionalLightDesc dlDesc;
	dlDesc.ambientIntensity = Vec4f{ 0.0f, 0.0f, 0.0f, 0.0f };
	dlDesc.diffuseIntensity = Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f };
	dlDesc.specularIntensity = Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f };

	DirectionalLight* dl{ new DirectionalLight{ "DirectionalLight1", dlDesc } };

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
	if (!ovrStage->Initialize())
	{
		BLADE_ERROR("Failed to initialize the ovr pass stage.");
		return false;
	}

	pipeline->AddStage(ovrStage);
#else
	//Allocate and initialize the a render pass pipeline stage.
	GameSceneColorPassStage* colorPassStage{ new GameSceneColorPassStage{ "GameSceneColorPass" } };
	if (!colorPassStage->Initialize())
	{
		BLADE_ERROR("Failed to initialize the color pass stage.");
		return false;
	}

	pipeline->AddStage(colorPassStage);
#endif

	//Set the pipeline to the render system.
	G_RenderSystem.SetRenderPassPipeline(pipeline);

	G_AudioManager.PlayStream(AUDIO_PATH + L"destructoid.ogg", 0.1f, AUDIO_PLAYMODE_LOOP);

	return true;

}

void MainScene::OnKeyDown(unsigned char key, int x, int y) noexcept
{

}

void MainScene::OnKeyUp(unsigned char key, int x, int y) noexcept
{

}

void MainScene::OnMouseMotion(int x, int y) noexcept
{

}

void MainScene::OnMouseClick(int button, bool state, int x, int y) noexcept
{

}

void MainScene::Update(float deltaTime, long time) noexcept
{
	Scene::Update(deltaTime, time);

	G_InputManager.Update(deltaTime);

	G_SimulationSystem.Process(deltaTime);

	G_LightSystem.Process();

	G_BehaviourSystem.Process(deltaTime, time);
}

void MainScene::Draw() const noexcept
{
	G_RenderSystem.Process();
}

