#include "command.h"
#include "entity.h"
#include "engine_context.h"
#include <iostream>


//Helper
/*
\brief Return the joy pad number associated with the entity.
\description It assumes that the check has been done before calling this function
*/
Blade::JoypadNumber GetJoypadNumberByEntity(Blade::Entity* entity)
{
	using namespace Blade;
	auto  comp = static_cast<JoypadInputComponent*>(entity->GetComponent("co_jpic"));
	return comp->m_JoypadNum;
}

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