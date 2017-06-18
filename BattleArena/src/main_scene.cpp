#include "main_scene.h"
#include "pipeline.h"
#include "d3d/D3D11_texture.h"
#include "windowing_service.h"
#include "directional_light_component.h"
#include "camera.h"
#include "directional_light.h"
#include <iostream>
#include "resource_utils.h"
#include "resource_manager.h"
#include "mesh_utils.h"
#include "engine_context.h"
#include "game_scene_color_pass.h"
#include "render_component.h"
#include <memory>
#include "networked_lobby_scene.h"
#include "game_scene.h"

#ifdef BLADE_BUILD_OVR
#include "game_scene_color_pass_ovr.h"
#endif


using namespace Blade;
using namespace ResourceUtils;


void MainScene::CheckInputDevice()
{
	if (G_InputManager.QueryDeviceState(JoypadNumber::JOYPAD1, InputSensor::STICK_LEFT))
	{
		auto vec{ G_InputManager.GetAnalogStickVector(JoypadNumber::JOYPAD1, InputSensor::STICK_LEFT) };
		if (vec.x > 0.4f)
			OnMove(Move::RIGHT);
		if (vec.x < -.4f)
			OnMove(Move::LEFT);
	}
	if (G_InputManager.QueryDeviceState(JoypadNumber::JOYPAD1, InputSensor::BTN_FACE_1)||
		G_InputManager.QueryDeviceState(JoypadNumber::JOYPAD1, InputSensor::BTN_OPTION_1))
	{
		OnPress();
	}

	if (G_InputManager.QueryKeyState(VirtualKey::KEY_SPACE) ||
		G_InputManager.QueryKeyState(VirtualKey::KEY_RETURN))
	{
		OnPress();
	}

	if (G_InputManager.QueryKeyState(VirtualKey::KEY_LEFT))
	{
		OnMove(Move::LEFT);
	}
	else if (G_InputManager.QueryKeyState(VirtualKey::KEY_RIGHT))
	{
		OnMove(Move::RIGHT);
	}


}

void MainScene::OnMove(Move move)
{
	if (move == Move::LEFT)
	{
		auto rc{ static_cast<RenderComponent*>(m_pScreen->GetComponent("co_render")) };
		auto material{ rc->GetMaterial() };
		material.textures[TEX_DIFFUSE] = G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"network-multiplayer.png");
		rc->SetMaterial(material);
		m_State = CurrentState::NETWORK;
	}
	else if (move == Move::RIGHT)
	{
		auto rc{ static_cast<RenderComponent*>(m_pScreen->GetComponent("co_render")) };
		auto material{ rc->GetMaterial() };
		material.textures[TEX_DIFFUSE] = G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"local-multiplayer.png");
		rc->SetMaterial(material);
		m_State = CurrentState::LOCAL;
	}
}

void MainScene::OnPress()
{
	if (m_State == CurrentState::LOGO) return;
	m_Fading = true;
	m_Timer.Start();
}

bool MainScene::Initialize()
{
	m_State = CurrentState::LOGO ;
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

	Texture* local{ G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"local-multiplayer.png") };
	local->SetTextureType(TEX_DIFFUSE);

	Texture* network{ G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"network-multiplayer.png") };
	network->SetTextureType(TEX_DIFFUSE);

	Texture* waiting{ G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"waiting-for-players.png") };
	waiting->SetTextureType(TEX_DIFFUSE);

	//////////////////////////////////////////////////////////////////////////
	Entity* arena{ new Entity{ "arena" } };
	arena->Load(L"data/models/main_menu.fbx");
	AddEntity(arena);



	m_pBillobard = arena->GetEntityFromHierarchy("Billboard");

	m_pScreen = arena->GetEntityFromHierarchy("SCREEN");
	//////////////////////////////////////////////////////////////////////////
	Vec2i windowSize{ WindowingService::GetWindow(0)->GetSize() };
	CameraDesc cd;
	cd.viewport = Viewport{ Recti{ 0, 0, windowSize }, 0.0f, 1.0f };
	cd.nearPlane = 0.1f;
	cd.farPlane = 500.0f;
	cd.fov = MathUtils::ToRadians(45.0f);

#ifdef BLADE_BUILD_OVR
	//Set the position of the camera.
	Camera* cam{ new Camera{ "Camera1", cd } };
	cam->SetPosition(Vec3f{ 0.0f, 2.23423f, -10.0f });
	//cam->SetOrientation(Vec3f{ 1.0f, 0.0f, 0.0f }, MathUtils::ToRadians(40.0f));
	AddEntity(cam);
	G_CameraSystem.SetActiveCamera("Camera1");
#else
	//Set the position of the camera.
	Camera* cam{ new Camera{ "Camera1", cd } };
	cam->SetPosition(Vec3f{ 0.0f, 5.23423f, -25.0f });
	//cam->SetOrientation(Vec3f{ 1.0f, 0.0f, 0.0f }, MathUtils::ToRadians(40.0f));
	AddEntity(cam);
	G_CameraSystem.SetActiveCamera("Camera1");
	// --------------------------------------------------------------------------------------------------------------------
#endif
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
	ovrStage = new GameSceneColorPassStageOvr{ " ovrPass " };
	ovrStage->scale = 2.5f;
	if (!ovrStage->Initialize())
	{
		BLADE_ERROR("Failed to initialize the ovr pass stage.");
		return false;
	}

	pipeline->AddStage(ovrStage);
#else
	//Allocate and initialize the a render pass pipeline stage.
	m_ColorPass = new GameSceneColorPassStage{ "GameSceneColorPass" };
	if (!m_ColorPass->Initialize())
	{
		BLADE_ERROR("Failed to initialize the color pass stage.");
		return false;
	}

	pipeline->AddStage(m_ColorPass);
#endif

	//Set the pipeline to the render system.
	G_RenderSystem.SetRenderPassPipeline(pipeline);

	G_AudioManager.PlayStream(AUDIO_PATH + L"hyper_sun.ogg", 0.1f, AUDIO_PLAYMODE_ONCE);

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

	CheckInputDevice();

	FadeOutLogic(deltaTime);
}

void MainScene::Draw() const noexcept
{
	G_RenderSystem.Process();
}

void MainScene::FadeOutLogic(float deltaTime) const
{
	if (m_Fading)
	{
#ifdef BLADE_BUILD_OVR
		ovrStage->UpdateBrightness(-0.6f*deltaTime);
#else
		m_ColorPass->UpdateBrightness(-0.6f*deltaTime);
#endif
	}
	if (m_Timer.GetSec() > 2.0f)
	{
		if (m_State == CurrentState::NETWORK)
		{
			G_SceneManager.PopScene();
			G_SceneManager.PushScene(std::make_unique<NetworkedLobbyScene>());
		}
		if (m_State == CurrentState::LOCAL)
		{
			G_AudioManager.StopStreams();
			G_SceneManager.PopScene();
			G_SceneManager.PushScene(std::make_unique<GameScene>());
		}
	}

}

