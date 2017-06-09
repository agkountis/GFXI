#include "test_joypad_component.h"
#include "commands_battle_arena.h"

using namespace Blade;


TestJoypadComponent::TestJoypadComponent(const std::string& type, Entity* parent, Player joypad_number):
	JoypadInputComponent(type,parent,joypad_number)
{

}

TestJoypadComponent::~TestJoypadComponent()
{

}

void TestJoypadComponent::Update(const float dt, const long time) noexcept
{
	for (auto pair : m_JoypadCommandMap)
	{
		if (/*Ask input manager the state of pair.first*/true)
		{
			pair.second->Execute(GetParent(), dt);
		}
	}
}

void TestJoypadComponent::SetUp() noexcept
{
	//This should be outside 
	auto a_command = std::make_shared<PrintA>();
	auto b_command = std::make_shared<PrintB>();
	m_JoypadCommandMap[JOYPAD_ENUM::a] = a_command;
	m_JoypadCommandMap[JOYPAD_ENUM::b] = b_command;

}

void TestJoypadComponent::Teardown() noexcept
{

}

