#include "test_joypad_component.h"
#include "commands_battle_arena.h"
#include "engine_context.h"
#include <iostream>
using namespace Blade;


TestJoypadComponent::TestJoypadComponent(Entity* parent, JoypadNumber joypad_number):
	JoypadInputComponent(parent,joypad_number)
{
}

TestJoypadComponent::~TestJoypadComponent()
{

}

void TestJoypadComponent::Update(const float dt, const long time) noexcept
{
	for (auto pair : m_JoypadCommandMap)
	{
		if (G_InputManager.QueryDeviceState(m_JoypadNum,pair.first))
		{
			pair.second->Execute(GetParent(), dt);
		}
	}
}

void TestJoypadComponent::Setup() noexcept
{
	//This should be outside 
	auto a_command = std::make_shared<PrintA>();
	auto b_command = std::make_shared<PrintB>();
	auto c_command = std::make_shared<PrintStick>();
	m_JoypadCommandMap[Input_Sensor::BTN_FACE_1] = a_command;
	m_JoypadCommandMap[Input_Sensor::BTN_FACE_2] = b_command;
	m_JoypadCommandMap[Input_Sensor::STICK_LEFT]= c_command;

}

void TestJoypadComponent::Teardown() noexcept
{

}

