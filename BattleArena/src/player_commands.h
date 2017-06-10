#include "test_commands_battle_arena.h"


class MoveCommand : public Blade::Command
{
public:
	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;
		auto vec{ G_InputManager.GetAnalogStickVector(GetJoypadNumberByEntity(entity),Input_Sensor::STICK_LEFT) };
		if (entity->GetComponent("co_sim"))
		{
			auto simComp = static_cast<SimulationComponent*>(entity->GetComponent("co_sim"));
			simComp->AddForce(Vec3f(vec.x, 0.0f, vec.y)*dt*1000.0f);
		}
	}
};