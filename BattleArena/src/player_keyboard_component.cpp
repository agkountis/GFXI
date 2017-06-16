#include "player_keyboard_component.h"
#include "player_commands.h"
#include "engine_context.h"
#include "virtual_keys.h"

using namespace Blade;


PlayerKeyboardComponent::PlayerKeyboardComponent(Entity* parent,bool online)
	: KeyboardInputComponent(parent,online)
{
}

void PlayerKeyboardComponent::Update(const float dt, const long time) noexcept
{
	for (auto key : m_KeyboardCommandMap)
	{
		if (G_InputManager.QueryKeyState(key.first))
		{
			key.second->Execute(GetParent(), 0.1f);
		}
	}
	//Mouse

	//Movement
	Entity* parent = GetParent();
	const Vec2f& mouseMovement{ G_InputManager.QueryMouseMovementNormalized() * 5.0f };

	//change orientation
	const Quatf& q = parent->GetOrientation();
	parent->SetOrientation(glm::rotate(q, mouseMovement.x * dt, glm::vec3(0, 1, 0)));

	//Buttons
	bool left{ G_InputManager.QueryMouseButtonState(MouseButton::LEFT) };
	bool right{ G_InputManager.QueryMouseButtonState(MouseButton::RIGHT) };
}

void PlayerKeyboardComponent::Setup() noexcept
{
	//Keyboard
	auto move_up_command = std::make_shared<MoveForward>(m_Online);
	auto move_down_command = std::make_shared<MoveBack>(m_Online);
	auto move_left_command = std::make_shared<MoveLeft>(m_Online);
	auto move_right_command = std::make_shared<MoveRight>(m_Online);
	auto shoot_left_command = std::make_shared<ShootLeftWeapon>(m_Online);
	auto shoot_right_command = std::make_shared<ShootRightWeapon>(m_Online);

	m_KeyboardCommandMap[KEY_W] = move_up_command;
	m_KeyboardCommandMap[KEY_A] = move_left_command;
	m_KeyboardCommandMap[KEY_S] = move_down_command;
	m_KeyboardCommandMap[KEY_D] = move_right_command;

	m_KeyboardCommandMap[KEY_J] = shoot_left_command;
	m_KeyboardCommandMap[KEY_K] = shoot_right_command;
}

void PlayerKeyboardComponent::Teardown() noexcept
{
}
