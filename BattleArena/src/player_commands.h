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
		auto vec2{ G_InputManager.GetAnalogStickVector(joypadNumber,Input_Sensor::STICK_RIGHT) };

		if (entity->GetComponent("co_sim"))
		{
			//auto rt_value{ G_InputManager.GetActiveDevice(joypadNumber)->GetCurrentState().triggerRight};
			auto simComp = static_cast<SimulationComponent*>(entity->GetComponent("co_sim"));
			
			  
		

			Quatf q = entity->GetOrientation();
			q=glm::rotate(q, vec2.x*dt, glm::vec3(0, 1, 0));
			entity->SetOrientation(q);

			Mat4f m = Mat4f(q);
			//m=glm::rotate(m, 45.0f, glm::vec3(0, 1, 0));
			
			simComp->AddForce(Vec3f(m*Vec4f(0.0f, 0.0f, vec.y,0))*dt*(10000.0f));
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