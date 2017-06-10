#include "player_joypad_component.h"
#include "engine_context.h"
#include "player_commands.h"

using namespace  Blade;

PlayerJoypadComponent::PlayerJoypadComponent(Blade::Entity* parent, Blade::JoypadNumber joypad_number):
	JoypadInputComponent(parent,joypad_number)
{

}

PlayerJoypadComponent::~PlayerJoypadComponent()
{

}

void PlayerJoypadComponent::Update(const float dt, const long time) noexcept
{
	for (auto pair : m_JoypadCommandMap)
	{
		if (G_InputManager.QueryDeviceState(m_JoypadNum, pair.first))
		{
			pair.second->Execute(GetParent(), dt);
		}
	}
}

void PlayerJoypadComponent::Setup() noexcept
{
	auto move_command = std::make_shared<MoveCommand>();
	auto shoot_left_command = std::make_shared<ShootLeftWeapon>();
	auto shoot_right_command = std::make_shared<ShootRightWeapon>();

	m_JoypadCommandMap[Input_Sensor::STICK_LEFT] = move_command;

	m_JoypadCommandMap[Input_Sensor::BTN_FACE_1] = shoot_left_command;
	m_JoypadCommandMap[Input_Sensor::TRIGGER_RIGHT] = shoot_right_command;
}

void PlayerJoypadComponent::Teardown() noexcept
{

}
