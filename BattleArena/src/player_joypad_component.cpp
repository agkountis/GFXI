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

	m_JoypadCommandMap[Input_Sensor::STICK_LEFT] = move_command;
}

void PlayerJoypadComponent::Teardown() noexcept
{

}
