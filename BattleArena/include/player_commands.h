#include "test_commands_battle_arena.h"
#include "weapon_component.h"

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


class ShootLeftWeapon : public Blade::Command
{
public:
	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;

		//#needtorefactor

		//Get the weapons vector
		if(entity->GetComponents("co_weapon").size()>0)
		{

			auto componentVector = (entity->GetComponents("co_weapon"));
			std::vector<WeaponComponent*> weaponsVector;
			for (auto component : componentVector)
			{
				weaponsVector.push_back(static_cast<WeaponComponent*>(component));
			}

			//If the we have one weapon
			if (weaponsVector.size()>0)
			{
				//Check if we have a left weapon
				for (auto weapon : weaponsVector)
				{
					if (weapon->m_WeaponPos == WeaponPosition::LEFT)
					{
						weapon->Shoot();
						return;
					}
				}
			}
		}

	}
};


class ShootRightWeapon : public Blade::Command
{
public:
	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;

		//#needtorefactor

		//Get the weapons vector
		if (entity->GetComponents("co_weapon").size() > 0)
		{

			auto componentVector = (entity->GetComponents("co_weapon"));
			std::vector<WeaponComponent*> weaponsVector;
			for (auto component : componentVector)
			{
				weaponsVector.push_back(static_cast<WeaponComponent*>(component));
			}

			//If the we have one weapon
			if (weaponsVector.size() > 0)
			{
				//Check if we have a left weapon
				for (auto weapon : weaponsVector)
				{
					if (weapon->m_WeaponPos == WeaponPosition::RIGHT)
					{
						weapon->Shoot();
						return;
					}
				}
			}
		}

	}
};