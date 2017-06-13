#ifndef PLAYER_COMMANDS_H_
#define PLAYER_COMMANDS_H_
#include "test_commands_battle_arena.h"
#include "weapon_component.h"
#include "player.h"

class MoveForward : public Blade::Command
{
public:
	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;
		if (entity->GetComponent("co_sim"))
		{
			auto simComp = static_cast<SimulationComponent*>(entity->GetComponent("co_sim"));

			Player* pl = dynamic_cast<Player*>(entity);
			if (pl)
			{
				const Vec3f& heading = pl->GetHeading();
				//BLADE_TRACE("HEADING ON MOVE: " << heading.x << ", " << heading.z);
				simComp->AddForce(heading * dt * (10000.0f));
			}
		}
	}
};

class MoveBack : public Blade::Command
{
public:
	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;
		if (entity->GetComponent("co_sim"))
		{
			auto simComp = static_cast<SimulationComponent*>(entity->GetComponent("co_sim"));
			Player* pl = dynamic_cast<Player*>(entity);
			if (pl)
			{
				const Vec3f& heading = pl->GetHeading();
				simComp->AddForce(-heading * dt * (10000.0f));
			}
		}
	}
};

class MoveLeft : public Blade::Command
{
public:
	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;
		using namespace Blade;
		if (entity->GetComponent("co_sim"))
		{
			auto simComp = static_cast<SimulationComponent*>(entity->GetComponent("co_sim"));
			//simComp->AddForce(Vec3f(-1.0f, 0.0f, 0.0f)*dt*(10000.0f));

			//change orientation
			Quatf q = entity->GetOrientation();
			//use orientation to influence the force that is being added to the simulation component
			simComp->AddForce(Vec3f(Mat4f(q) * Vec4f(-1.0f, 0.0f, 0.0f, 0)) * dt * (1000.0f));
		}
	}
};


class MoveRight : public Blade::Command
{
public:
	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;
		if (entity->GetComponent("co_sim"))
		{
			auto simComp = static_cast<SimulationComponent*>(entity->GetComponent("co_sim"));
			//change orientation
			Quatf q = entity->GetOrientation();
			//use orientation to influence the force that is being added to the simulation component
			simComp->AddForce(Vec3f(Mat4f(q) * Vec4f(1.0f, 0.0f, 0.0f, 0)) * dt * (1000.0f));
		}
	}
};


class MoveCommand : public Blade::Command
{
public:
	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;
		auto joypadNumber{ GetJoypadNumberByEntity(entity) };
		auto movementVec{ G_InputManager.GetAnalogStickVector(joypadNumber, InputSensor::STICK_LEFT) };
		auto rotationVec{ G_InputManager.GetAnalogStickVector(joypadNumber, InputSensor::STICK_RIGHT) };


		if (entity->GetComponent("co_sim"))
		{
			//auto rt_value{ G_InputManager.GetActiveDevice(joypadNumber)->GetCurrentState().triggerRight};
			auto simComp = static_cast<SimulationComponent*>(entity->GetComponent("co_sim"));

			//change orientation
			Quatf q = entity->GetOrientation();
			entity->SetOrientation(glm::rotate(q, rotationVec.x * dt, glm::vec3(0, 1, 0)));

			//use orientation to influence the force that is being added to the simulation component
			simComp->AddForce(Vec3f(Mat4f(q) * Vec4f(movementVec.x * 0.5f, 0.0f, movementVec.y, 0)) * dt * (2000.0f));
		}
		Player* pl = dynamic_cast<Player*>(entity);
		if (pl)
		{
			pl->GetHeading();
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

		auto p{ static_cast<Player*>(entity) };

		//Get the weapons vector
		if (entity->GetComponents("co_weapon").size() > 0)
		{
			auto componentVector = entity->GetComponents("co_weapon");

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
					if (weapon->GetWeaponPosition() == WeaponPosition::LEFT)
					{
						weapon->Shoot(p->GetLeftWeaponPos());
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

		auto p{ static_cast<Player*>(entity) };

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
					if (weapon->GetWeaponPosition() == WeaponPosition::RIGHT)
					{
						weapon->Shoot(p->GetRightWeaponPos());
						return;
					}
				}
			}
		}
	}
};

#endif