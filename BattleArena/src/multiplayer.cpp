#include "multiplayer.h"
#include "serialization_utils.h"
#include <iostream>
#include "network_message_types.h"
#include "engine_context.h"
#include "command_message.h"
#include "ncf.h"
#include "trace.h"
#include "player_commands.h"

using namespace Blade;
using namespace SerializationUtils;

namespace Multiplayer
{
	void Multiplayer::OnNewClient(ConnectionInfo connectionInfo)
	{
		BLADE_TRACE("New Player Connected!!!");
		BLADE_TRACE(std::get<std::string>(connectionInfo.ip));
		BLADE_TRACE(std::to_string(std::get<unsigned long>(connectionInfo.ip)));
	}

	void Multiplayer::OnClientDisconnect()
	{
		std::cout << "Player Disconnected!!!" << std::endl;
	}

	void Multiplayer::OnNewPacket(std::vector<Byte> packet)
	{
		int packetSize{ 0 };
		int offset{ 0 };

		Unpack(packet, offset, packetSize);
		offset += sizeof packetSize;

		if (packetSize != packet.size())
		{
			throw std::exception{ "Packet length missmatch!" };
		}

		int msgType;
		Unpack(packet, offset, msgType);
		offset += sizeof msgType;
		int playerID;
		Unpack(packet, offset, playerID);
		offset += sizeof playerID;
		const std::string playerString{ "player"+std::to_string(playerID) };
		auto player{ static_cast<Player*>(G_SceneManager.GetCurrentScene()->GetEntityByName(playerString)) };

		switch (msgType)
		{
		case BA_SHOOT_LEFT:
		{
			ShootLeftWeapon command{false};
			command.Execute(player, 0.1f);
		}
			break;

		case BA_SHOOT_RIGHT:
		{
			ShootRightWeapon command{ false };
			command.Execute(player, 0.1f);
		}
			break;

		case BA_MOVE_BY_VEC:
		{
			Vec3f rotation;
			Unpack<Vec3f>(packet, offset, rotation);
			offset += sizeof rotation;
			Vec3f movement;
			Unpack<Vec3f>(packet, offset, movement);
			offset += sizeof movement;
			NetworkMoveCommand command{ false,rotation,movement };
			command.Execute(player,0.1f);
		}
			break;

		case BA_MOVE_FORWARD:
		{
			MoveForward command{ false };
			command.Execute(player, 0.1f);
		}
			break;

		case BA_MOVE_BACK:
		{
			MoveBack command{ false };
			command.Execute(player, 0.1f);
		}
			break;

		case BA_MOVE_LEFT:
		{
			MoveLeft command{ false };
			command.Execute(player, 0.1f);
		}
			break;

		case BA_MOVE_RIGHT:
		{
			MoveRight command{ false };
			command.Execute(player, 0.1f);
		}
			break;
		default:
			break;
		}
	}
}
