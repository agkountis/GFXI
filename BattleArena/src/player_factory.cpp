#include "player_factory.h"
#include "engine_context.h"
#include "player_keyboard_component.h"
#include "player_joypad_component.h"
#include "player_behaviour.h"
#include "bounding_sphere.h"
#include "simulation_component.h"
#include "collider_component.h"

using namespace Blade;

Player* PlayerFactory::CreateLocalKeyboardPlayer(const std::string& name, const std::wstring& modelPath)
{
	auto player{ CreateMultiplayerPlayer(name,modelPath) };
	PlayerKeyboardComponent* pkc{ new PlayerKeyboardComponent{player} };
	pkc->Setup();
	m_KeyboardPlayer = true;
	return player;
}


Player* PlayerFactory::CreateLocalJoypadPlayer(const std::string& name, const std::wstring& modelPath)
{
	auto player{ CreateMultiplayerPlayer(name,modelPath) };
	auto counter{ m_KeyboardPlayer ? m_Counter - 2 : m_Counter - 1 };
	JoypadNumber joypadNumber{ static_cast<JoypadNumber>(counter) };
	PlayerJoypadComponent* pjc{ new PlayerJoypadComponent{player,joypadNumber} };
	pjc->Setup();
	return player;
}

Player * PlayerFactory::CreateMultiplayerPlayer(const std::string & name, const std::wstring & modelPath)
{
	Player* player{ new Player{ name } };

	player->Load(MODELS_PATH + modelPath);
	//#question 
	Blade::SimulationComponent* simC3{ new Blade::SimulationComponent{ player,1.0f } };

	PlayerBehaviour* pb = new PlayerBehaviour(player, true);
	Blade::ColliderComponent* colC3{ new Blade::ColliderComponent{ player,std::make_unique<Blade::BoundingSphere>(1.0f) } };
	colC3->SetListener(pb);
	m_Counter++;
	return player;
}



