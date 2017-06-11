#ifndef BLADE_PLAYER_KEYBOARD_COMPONENT_H_
#define BLADE_PLAYER_KEYBOARD_COMPONENT_H_

#include "keyboard_input_component.h"

class PlayerKeyboardComponent : public Blade::KeyboardInputComponent
{
public:
	PlayerKeyboardComponent(Blade::Entity* parent);

	~PlayerKeyboardComponent();

	void Update(const float dt, const long time) noexcept override;

	void Setup() noexcept override;

	void Teardown() noexcept override;
};


#endif//BLADE_PLAYER_KEYBOARD_COMPONENT_H_