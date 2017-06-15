#include "multiplayer.h"
#include "serialization_utils.h"
#include <iostream>
#include "network_message_types.h"
#include "engine_context.h"
#include "command_message.h"
#include "ncf.h"
#include "trace.h"

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

		switch (msgType)
		{
		case BA_SHOOT_LEFT:
			break;

		case BA_SHOOT_RIGHT:
			break;

		case BA_MOVE_BY_VEC:
			break;

		case BA_MOVE_FORWARD:
			break;

		case BA_MOVE_BACK:
			break;

		case BA_MOVE_LEFT:
			break;

		case BA_MOVE_RIGHT:
			break;
		default:
			break;
		}
	}
}
