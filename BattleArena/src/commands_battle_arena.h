#include "command.h"
#include "entity.h"
#include <iostream>
#include "test_joypad_component.h"
#include "engine_context.h"



class PrintA : public Blade::Command
{
public:
	void Execute(Blade::Entity* entity, const float dt) override
	{
		std::cout << "a" << std::endl;
	}

};

class PrintB : public Blade::Command
{
public:
	void Execute(Blade::Entity* entity, const float dt) override
	{
		std::cout << "b" << std::endl;
	}
};


class PrintStick : public Blade::Command
{
	
public:
	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;
		auto vec{ G_InputManager.GetAnalogStickVector(GetJoypadNumberByEntity(entity),Input_Sensor::STICK_LEFT)} ;
	
		std::cout << vec.x <<", "<<vec.y << std::endl;
	}
};