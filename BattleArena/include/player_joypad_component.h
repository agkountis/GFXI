#ifndef BLADE_PLAYER_JOYPAD_COMPONENT_H_
#define BLADE_PLAYER_JOYPAD_COMPONENT_H_
#include "joypad_input_component.h"

class PlayerJoypadComponent : public Blade::JoypadInputComponent
{
public:
	PlayerJoypadComponent(Blade::Entity* parent, Blade::JoypadNumber joypad_number);

	~PlayerJoypadComponent();

	void Update(const float dt, const long time) noexcept override;

	void Setup() noexcept override;

	void Teardown() noexcept override;

};

#endif//BLADE_PLAYER_JOYPAD_COMPONENT_H_