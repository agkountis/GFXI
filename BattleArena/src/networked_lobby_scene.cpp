#include "networked_lobby_scene.h"
#include "cfg.h"
#include "resource_manager.h"
#include "engine_context.h"
#include "networked_game_scene.h"
#include "multiplayer.h"
#include "command_message.h"

using namespace Blade;
using namespace StringUtils;

bool NetworkedLobbyScene::Initialize()
{
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
	switch (key)
	{
	case 's':
	case 'S':
		G_SceneManager.PushScene(std::make_unique<NetworkedGameScene>(m_PlayerInfos));
		break;
	default:
		break;
	}
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
}

void NetworkedLobbyScene::Update(float deltaTime, long time) noexcept
{
}
