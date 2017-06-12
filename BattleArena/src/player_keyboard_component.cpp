#include "player_keyboard_component.h"
#include "player_commands.h"
#include "engine_context.h"
#include "virtual_keys.h"

using namespace Blade;


PlayerKeyboardComponent::PlayerKeyboardComponent(Blade::Entity* parent):
	KeyboardInputComponent(parent)
{

}

PlayerKeyboardComponent::~PlayerKeyboardComponent()
{

}

void PlayerKeyboardComponent::Update(const float dt, const long time) noexcept
{
	for (auto key : m_KeyboardCommandMap)
	{
		if (G_InputManager.QueryKeyState(key.first))
		{
			key.second->Execute(GetParent(), dt);
		}
	}
	//Mouse
	Entity* parent = GetParent();
	const Vec2f& mouseMovement{ G_InputManager.QueryMouseMovementNormalized()*5.0f};
	//change orientation
	const Quatf& q = parent->GetOrientation();
	parent->SetOrientation(glm::rotate(q, mouseMovement.x*dt, glm::vec3(0, 1, 0)));

}

void PlayerKeyboardComponent::Setup() noexcept
{
	//Keyboard
	auto move_up_command = std::make_shared<MoveForward>();
	auto move_down_command = std::make_shared<MoveBack>();
	auto move_left_command = std::make_shared<MoveLeft>();
	auto move_right_command = std::make_shared<MoveRight>();
	auto shoot_left_command = std::make_shared<ShootLeftWeapon>();
	auto shoot_right_command = std::make_shared<ShootRightWeapon>();

	m_KeyboardCommandMap[Virtual_Key::KEY_W] = move_up_command;
	m_KeyboardCommandMap[Virtual_Key::KEY_A] = move_left_command;
	m_KeyboardCommandMap[Virtual_Key::KEY_S] = move_down_command;
	m_KeyboardCommandMap[Virtual_Key::KEY_D] = move_right_command;

	m_KeyboardCommandMap[Virtual_Key::KEY_J] = shoot_left_command;
	m_KeyboardCommandMap[Virtual_Key::KEY_K] = shoot_right_command;


}

void PlayerKeyboardComponent::Teardown() noexcept
{

}
