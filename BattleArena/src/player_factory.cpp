#include "player_factory.h"
#include "engine_context.h"
#include "player_keyboard_component.h"
#include "player_joypad_component.h"
#include "player_behaviour.h"
#include "bounding_sphere.h"
#include "simulation_component.h"
#include "collider_component.h"
#include "health_component.h"

using namespace Blade;

Player* PlayerFactory::CreateLocalKeyboardPlayer(const std::string& name, const std::wstring& modelPath) noexcept
{
	auto player{ CreateMultiplayerPlayer(name, modelPath) };
	PlayerKeyboardComponent* pkc{ new PlayerKeyboardComponent{ player } };
	pkc->Setup();
	m_KeyboardPlayer = true;
	return player;
}


Player* PlayerFactory::CreateLocalJoypadPlayer(const std::string& name, const std::wstring& modelPath) noexcept
{
	auto player{ CreateMultiplayerPlayer(name, modelPath) };
	auto counter{ m_KeyboardPlayer ? m_Counter - 2 : m_Counter - 1 };
	JoypadNumber joypadNumber{ static_cast<JoypadNumber>(counter) };
	PlayerJoypadComponent* pjc{ new PlayerJoypadComponent{ player,joypadNumber } };
	pjc->Setup();
	return player;
}

Player* PlayerFactory::CreateMultiplayerPlayer(const std::string& name, const std::wstring& modelPath) noexcept
{
	Player* player{ new Player{ name } };

	player->Load(MODELS_PATH + modelPath);

	SimulationComponent* simC3{ new SimulationComponent{ player,1.0f } };

	PlayerBehaviour* pb = new PlayerBehaviour(player, true);
	ColliderComponent* colC3{ new ColliderComponent{ player,std::make_unique<BoundingSphere>(1.0f) } };
#if _DEBUG
	RenderComponent *rc{ new RenderComponent{player} };
	Material material;
	material.diffuse = Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f };
	material.specular = Vec4f{ 1.0f, 1.0f, 1.0f, 60.0f }; //the w value is the shininess.
	rc->SetMesh(G_ResourceManager.Get<Mesh>(L"cube"));
	rc->SetMaterial(material);
#endif
	colC3->AddListener(pb);

	HealthComponent* hcom{ new HealthComponent(player) };
	colC3->AddListener(hcom);
	player->SetWeaponPositions(player->GetEntityFromHierarchy("LeftWeaponSocket")->GetLocalPosition(), player->GetEntityFromHierarchy("RightWeaponSocket")->GetLocalPosition());
	m_Counter++;
	return player;
}
