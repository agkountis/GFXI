#include "test_commands_battle_arena.h"


class MoveCommand : public Blade::Command
{
public:
	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;
		auto joypadNumber{ GetJoypadNumberByEntity(entity) };
		auto vec{ G_InputManager.GetAnalogStickVector(joypadNumber,Input_Sensor::STICK_LEFT) };
		if (entity->GetComponent("co_sim"))
		{
			//auto rt_value{ G_InputManager.GetActiveDevice(joypadNumber)->GetCurrentState().triggerRight};
			auto simComp = static_cast<SimulationComponent*>(entity->GetComponent("co_sim"));
			simComp->AddForce(Vec3f(vec.x, 0.0f, vec.y)*dt*(10000.0f));
		}
	}
};