#ifndef BLADE_TEST_JOYPAD_COMPONENT_H_
#define BLADE_TEST_JOYPAD_COMPONENT_H_
#include "joypad_input_component.h"

class TestJoypadComponent : public Blade::JoypadInputComponent
{
	TestJoypadComponent(const std::string& type, Blade::Entity* parent, Blade::Player joypad_number);
	
	~TestJoypadComponent();

	void Update(const float dt, const long time) noexcept override;

	void SetUp() noexcept override;

	void Teardown() noexcept override;

};

#endif//BLADE_TEST_JOYPAD_COMPONENT_H_