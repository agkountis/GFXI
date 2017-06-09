#include "command.h"
#include "entity.h"
#include <iostream>
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
		std::cout << "AAA" << std::endl;
	}
};