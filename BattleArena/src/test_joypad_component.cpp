//#include "test_joypad_component.h"
//#include "engine_context.h"
//#include <iostream>
//#include "test_commands_battle_arena.h"
//
//using namespace Blade;
//
//
//TestJoypadComponent::TestJoypadComponent(Entity* parent, JoypadNumber joypad_number):
//	JoypadInputComponent(parent,joypad_number)
//{
//}
//
//TestJoypadComponent::~TestJoypadComponent()
//{
//
//}
//
//void TestJoypadComponent::Update(const float dt, const long time) noexcept
//{
//	for (auto pair : m_JoypadCommandMap)
//	{
//		if (G_InputManager.QueryDeviceState(m_JoypadNum,pair.first))
//		{
//			pair.second->Execute(GetParent(), dt);
//		}
//	}
//}
//
//void TestJoypadComponent::Setup() noexcept
//{
//	//This should be outside 
//	auto a_command = std::make_shared<PrintA>();
//	auto b_command = std::make_shared<PrintB>();
//	auto x_command = std::make_shared<PrintX>();
//	auto y_command = std::make_shared<PrintY>();
//	auto rb_command = std::make_shared<PrintRB>();
//	auto rt_command = std::make_shared<PrintRT>();
//	auto lb_command = std::make_shared<PrintLB>();
//	auto lt_command = std::make_shared<PrintLT>();
//	auto start_command = std::make_shared<PrintStart>();
//	auto select_command = std::make_shared<PrintSelect>();
//	auto left_stick_command = std::make_shared<PrintLeftStick>();
//	auto right_stick_command = std::make_shared<PrintRightStick>();
//
//
//	m_JoypadCommandMap[Input_Sensor::BTN_FACE_1] = a_command;
//	m_JoypadCommandMap[Input_Sensor::BTN_FACE_2] = b_command;
//	m_JoypadCommandMap[Input_Sensor::BTN_FACE_3] = x_command;
//	m_JoypadCommandMap[Input_Sensor::BTN_FACE_4] = y_command;
//
//	m_JoypadCommandMap[Input_Sensor::BTN_SHOULDER_R] = rb_command;
//	m_JoypadCommandMap[Input_Sensor::TRIGGER_RIGHT] = rt_command;
//	m_JoypadCommandMap[Input_Sensor::BTN_SHOULDER_L] = lb_command;
//	m_JoypadCommandMap[Input_Sensor::TRIGGER_LEFT] = lt_command;
//
//	m_JoypadCommandMap[Input_Sensor::BTN_OPTION_1] = start_command;
//	m_JoypadCommandMap[Input_Sensor::BTN_OPTION_2] = select_command;
//
//	m_JoypadCommandMap[Input_Sensor::STICK_LEFT]= left_stick_command;
//	m_JoypadCommandMap[Input_Sensor::STICK_RIGHT] = right_stick_command;
//
//}
//
//void TestJoypadComponent::Teardown() noexcept
//{
//
//}
//
