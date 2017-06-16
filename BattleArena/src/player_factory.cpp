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


Player* PlayerFactory::CreateKeyboardPlayer(const std::string& name, const std::wstring& modelPath, const int playerID, bool online) noexcept
{
	auto player{ CreatePlayer(name, modelPath,playerID) };
	PlayerKeyboardComponent* pkc{ new PlayerKeyboardComponent{ player,online } };
	pkc->Setup();
	m_KeyboardPlayer = true;
	return player;
}


Player* PlayerFactory::CreateJoypadPlayer(const std::string& name, const std::wstring& modelPath, const int playerID, bool online) noexcept
{
	auto player{ CreatePlayer(name, modelPath,playerID) };
	auto counter{ m_KeyboardPlayer ? m_Counter - 2 : m_Counter - 1 };
	JoypadNumber joypadNumber{ static_cast<JoypadNumber>(counter) };
	PlayerJoypadComponent* pjc{ new PlayerJoypadComponent{ player,joypadNumber,online } };
	pjc->Setup();
	return player;
}

Player* PlayerFactory::CreatePlayer(const std::string& name, const std::wstring& modelPath,const int playerID) noexcept
{
	Player* player{ new Player{ name,playerID } };

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

	HealthBar* hb{ m_HealthBarFactory.CreateHealthBar(player,100) };
    hb->SetHealthValue(100);

	hcom->SetListenerBar(hb);
	player->SetWeaponPositions(player->GetEntityFromHierarchy("LeftWeaponSocket")->GetLocalPosition(), player->GetEntityFromHierarchy("RightWeaponSocket")->GetLocalPosition());

	m_Counter++;
	return player;
}
