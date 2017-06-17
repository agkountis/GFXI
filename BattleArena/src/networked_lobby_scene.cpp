#include "networked_lobby_scene.h"
#include "cfg.h"
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
#include "multiplayer.h"
#include "networked_game_scene.h"

#ifdef BLADE_BUILD_OVR
#include "game_scene_color_pass_ovr.h"
#endif


using namespace Blade;
using namespace StringUtils;

bool NetworkedLobbyScene::Initialize()
{
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

	auto rc{ static_cast<RenderComponent*>(m_pScreen->GetComponent("co_render")) };
	auto material{ rc->GetMaterial() };
	material.textures[TEX_DIFFUSE] = G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"waiting-for-players.png");
	//material.textures[TEX_DIFFUSE]->SetTextureType(TEX_DIFFUSE);
	rc->SetMaterial(material);

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


	ConfigFile cfg;

	std::wstring fname{ L"test.cfg" };
	cfg.Open(ToString(CONFIGURATION_PATH + fname).c_str());

	if (!cfg.IsOpen())
	{
		BLADE_ERROR("Failed to load " + ToString(fname));
		return false;
	}

	std::string playerName{ cfg.GetString("attributes.player") };

	Vec4f sLoc{ cfg.GetVec4f("attributes.spawnLocation") };

	m_PlayerInfos.emplace_back(playerName, ToWstring(playerName) + L".fbx", sLoc.xyz);

	unsigned short port = cfg.GetInteger("attributes.listenTo.port", 0);

	G_NetworkManager.Listen(port);

	G_NetworkManager.SetOnNewClientCallback(Multiplayer::OnNewClient);
	G_NetworkManager.SetOnNewPacketCallback(Multiplayer::OnNewPacket);
	G_NetworkManager.SetOnClientDisconnectCallback(Multiplayer::OnClientDisconnect);

	NCF* node{ cfg.GetNcf() };

	if (!node)
	{
		return false;
	}

	node = node->GetGroupByName("attributes")->GetGroupByName("connectTo");

	for (int i = 0; i < node->CountGroups(); ++i)
	{
		NCF* child = node->GetGroupByIndex(i);
		std::string name{ child->GetName() };
		std::string ip;
		Vec4f spawnLocation;

		for (int j = 0; j < child->CountProperties(); ++j)
		{
			ip = child->GetPropertyByName("ip");

			ConfigFile c;
			c.SetNcf(child);

			spawnLocation = c.GetVec4f("spawnLocation");
		}

		m_PlayerInfos.emplace_back(name, ToWstring(name) + L".fbx", spawnLocation.xyz);

		G_NetworkManager.Connect(ip, port);
	}


	BLADE_TRACE("Players connected. Press 's' to start.");

	return true;
}

void NetworkedLobbyScene::OnKeyDown(unsigned char key, int x, int y) noexcept
{
}

void NetworkedLobbyScene::OnKeyUp(unsigned char key, int x, int y) noexcept
{
}

void NetworkedLobbyScene::OnMouseMotion(int x, int y) noexcept
{
}

void NetworkedLobbyScene::OnMouseClick(int button, bool state, int x, int y) noexcept
{
}

void NetworkedLobbyScene::Draw() const noexcept
{
	G_RenderSystem.Process();
}

void NetworkedLobbyScene::Update(float deltaTime, long time) noexcept
{
	Scene::Update(deltaTime, time);

	G_LightSystem.Process();

	G_BehaviourSystem.Process(deltaTime, time);

	if (G_NetworkManager.GetConnectionCount() == 3)
	{
		G_SceneManager.PopScene();
		G_SceneManager.PushScene(std::make_unique<NetworkedLobbyScene>());
	}

}
