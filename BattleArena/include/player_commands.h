#ifndef PLAYER_COMMANDS_H_
#define PLAYER_COMMANDS_H_
#include "test_commands_battle_arena.h"
#include "weapon_component.h"
#include "player.h"
#include "command_message.h"
#include "network_message_types.h"

class MoveForward : public Blade::Command
{
public:
	MoveForward(bool online) :Blade::Command(online) {}

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

				if (m_Online)
				{
					//std::cout << "Sending... move forward" << std::endl;
					G_NetworkManager.QueueMessage(std::make_shared<CommandMessage>(pl->GetID(), BA_MOVE_FORWARD, RECIPIENT_ID_BROADCAST, nullptr));
				}

			}
		}
	}
};

class MoveBack : public Blade::Command
{
public:
	MoveBack(bool online) :Blade::Command(online) {}

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
				if (m_Online)
				{
					//std::cout << "Sending... move back" << std::endl;
					G_NetworkManager.QueueMessage(std::make_shared<CommandMessage>(pl->GetID(), BA_MOVE_BACK, RECIPIENT_ID_BROADCAST, nullptr));
				}
			}
		}
	}
};

class MoveLeft : public Blade::Command
{
public:
	MoveLeft(bool online) :Blade::Command(online) {}
	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;
		using namespace Blade;
		if (entity->GetComponent("co_sim"))
		{
			auto simComp = static_cast<SimulationComponent*>(entity->GetComponent("co_sim"));
			//simComp->AddForce(Vec3f(-1.0f, 0.0f, 0.0f)*dt*(10000.0f));
			Player* pl = static_cast<Player*>(entity);
			//change orientation
			Quatf q = entity->GetOrientation();
			//use orientation to influence the force that is being added to the simulation component
			simComp->AddForce(Vec3f(Mat4f(q) * Vec4f(-1.0f, 0.0f, 0.0f, 0)) * dt * (1000.0f));
			if (m_Online)
			{
				//std::cout << "Sending... move left" << std::endl;
				G_NetworkManager.QueueMessage(std::make_shared<CommandMessage>(pl->GetID(), BA_MOVE_LEFT, RECIPIENT_ID_BROADCAST, nullptr));
			}
		}
	}
};


class MoveRight : public Blade::Command
{
public:
	MoveRight(bool online) :Blade::Command(online) {}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;
		if (entity->GetComponent("co_sim"))
		{
			auto simComp = static_cast<SimulationComponent*>(entity->GetComponent("co_sim"));
			//change orientation
			Player* pl = static_cast<Player*>(entity);

			Quatf q = entity->GetOrientation();
			//use orientation to influence the force that is being added to the simulation component
			simComp->AddForce(Vec3f(Mat4f(q) * Vec4f(1.0f, 0.0f, 0.0f, 0)) * dt * (1000.0f));
			if (m_Online)
			{
				//std::cout << "Sending... move right" << std::endl;
				G_NetworkManager.QueueMessage(std::make_shared<CommandMessage>(pl->GetID(), BA_MOVE_RIGHT, RECIPIENT_ID_BROADCAST, nullptr));
			}
		}
	}
};


class MoveCommand : public Blade::Command
{
public:
	MoveCommand(bool online) :Blade::Command(online) {}

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

class NetworkMoveCommand : public Blade::Command
{
private:
	Blade::Vec3f rotationVec;
	Blade::Vec3f movementVec;
public:
	NetworkMoveCommand(bool online, const Blade::Vec3f& rotation, const Blade::Vec3f& movement) :Blade::Command(online),
	rotationVec{rotation}, movementVec{movement}
	{}

	void Execute(Blade::Entity* entity, const float dt) override
	{
		using namespace Blade;


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
	ShootLeftWeapon(bool online) :Blade::Command(online) {}

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
						if (m_Online)
						{
							//std::cout << "Sending... shoot left" << std::endl;
							G_NetworkManager.QueueMessage(std::make_shared<CommandMessage>(p->GetID(), BA_SHOOT_LEFT, RECIPIENT_ID_BROADCAST, nullptr));
						}
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
	ShootRightWeapon(bool online) :Blade::Command(online) {}

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
						if (m_Online)
						{
							//std::cout << "Sending... right left" << std::endl;
							G_NetworkManager.QueueMessage(std::make_shared<CommandMessage>(p->GetID(), BA_SHOOT_RIGHT, RECIPIENT_ID_BROADCAST, nullptr));
						}
						return;
					}
				}
			}
		}
	}
};



#endif