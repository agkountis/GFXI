#include "packet_handler.h"
#include "serialization_utils.h"
#include <iostream>
#include "network_message_types.h"
#include "engine_context.h"
#include "test_message.h"

using namespace Blade;
using namespace SerializationUtils;

void OnNewClient()
{
	std::cout << "New Player Connected!!!" << std::endl;
}

void OnClientDisconnect()
{
	std::cout << "Player Disconnected!!!" << std::endl;
}

void OnNewPacket(std::vector<Byte> packet)
{
	int packetSize{ 0 };
	int offset{ 0 };

	Unpack(packet, offset, packetSize);
	offset += sizeof packetSize;

	if (packetSize != packet.size()) {
		throw std::exception{ "Packet length missmatch!" };
	}

	int msgType;
	Unpack(packet, offset, msgType);
	offset += sizeof msgType;

	switch (msgType)
	{
	case BA_TEST_MESSAGE:
		int val;
		Unpack(packet, offset, val);

		if (val == 0)
		{
			std::cout << "Hello!: " << val << std::endl;
			G_NetworkManager.QueueMessage(std::make_shared<TestMessage>(1));
		}
		else if (val == 1)
		{
			std::cout << "Hey there!" << val << std::endl;
			G_NetworkManager.QueueMessage(std::make_shared<TestMessage>(0));
		}
		else
		{
			BLADE_ERROR("Unercognised TestMessage value!");
		}

		break;
	default:
		break;
	}
}
