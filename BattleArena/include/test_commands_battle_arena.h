#ifndef TEST_COMMANDS_H_
#define TEST_COMMANDS_H_

#include "command.h"
#include "entity.h"
#include "engine_context.h"
#include <iostream>
#include "joypad_input_component.h"


/*
\brief Return the joy pad number associated with the entity.
\description It assumes that the check has been done before calling this function
*/
Blade::JoypadNumber GetJoypadNumberByEntity(Blade::Entity* entity);

class PrintA : public Blade::Command
{
public:
	PrintA(bool online) :Blade::Command(online) {}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		std::cout << "A" << std::endl;
	}

};

class PrintB : public Blade::Command
{
public:
	PrintB(bool online) :Blade::Command(online) {}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		std::cout << "B" << std::endl;
	}
};

class PrintY : public Blade::Command
{
public:
	PrintY(bool online) :Blade::Command(online) {}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		std::cout << "Y" << std::endl;
	}
};

class PrintX : public Blade::Command
{
public:
	PrintX(bool online) :Blade::Command(online) {}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		std::cout << "X" << std::endl;
	}
};

class PrintRB : public Blade::Command
{
public:
	PrintRB(bool online) :Blade::Command(online) {}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		std::cout << "RB" << std::endl;
	}
};

class PrintRT : public Blade::Command
{
public:
	PrintRT(bool online) :Blade::Command(online) {}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		std::cout << "RT" << std::endl;
	}
};

class PrintLB : public Blade::Command
{
public:
	PrintLB(bool online) :Blade::Command(online) {}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		std::cout << "LB" << std::endl;
	}
};

class PrintLT : public Blade::Command
{
public:
	PrintLT(bool online) :Blade::Command(online) {}
	
	void Execute(Blade::Entity* entity, const float dt) override
	{
		std::cout << "LT" << std::endl;
	}
};

class PrintStart : public Blade::Command
{
public:
	PrintStart(bool online) :Blade::Command(online) {}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		std::cout << "START" << std::endl;
	}
};

class PrintSelect : public Blade::Command
{
public:
	PrintSelect(bool online) :Blade::Command(online) {}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		std::cout << "SELECT" << std::endl;
	}
};


class PrintLeftStick : public Blade::Command
{
public:
	PrintLeftStick(bool online) :Blade::Command(online) {}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;
		auto vec{ G_InputManager.GetAnalogStickVector(GetJoypadNumberByEntity(entity),InputSensor::STICK_LEFT)} ;

		std::cout <<"STICK_LEFT"<< vec.x <<", "<<vec.y << std::endl;
	}
};

class PrintRightStick : public Blade::Command
{
public:
	PrintRightStick(bool online) :Blade::Command(online) {}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;
		auto vec{ G_InputManager.GetAnalogStickVector(GetJoypadNumberByEntity(entity),InputSensor::STICK_RIGHT) };

		std::cout << "STICK_RIGHT" << vec.x << ", " << vec.y << std::endl;
	}
};

#endif