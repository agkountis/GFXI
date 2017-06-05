#include "multiplayer.h"
#include "serialization_utils.h"
#include <iostream>
#include "network_message_types.h"
#include "engine_context.h"
#include "test_message.h"
#include "ncf.h"

using namespace Blade;
using namespace SerializationUtils;

void Multiplayer::OnNewClient(ConnectionInfo connectionInfo)
{
	BLADE_TRACE("New Player Connected!!!");
	BLADE_TRACE(std::get<std::string>(connectionInfo.ip));
	BLADE_TRACE(std::to_string(std::get<long>(connectionInfo.ip)));
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
	case BA_TEST_MESSAGE:
		int val;
		Unpack(packet, offset, val);

		if (val == 0)
		{
			std::cout << "Hello!: " << val << std::endl;
			G_NetworkManager.QueueMessage(std::make_shared<TestMessage>(1, RECIPIENT_ID_BROADCAST));
		}
		else if (val == 1)
		{
			std::cout << "Hey there!" << val << std::endl;
			G_NetworkManager.QueueMessage(std::make_shared<TestMessage>(0, RECIPIENT_ID_BROADCAST));
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

bool Multiplayer::Initialize(const std::string& networkConfigFileName) noexcept
{
	NCF ncf;
	ncf.SetSource(networkConfigFileName.c_str());

	if (ncf.Parse())
	{
		BLADE_ERROR("Failed to parse the configuration file.");
		return false;
	}

	NCF* group{ ncf.GetGroupByName("attributes") };

	if (!group->QueryGroup("listenTo"))
	{
		BLADE_ERROR("Multiplayer initialization failed. Missing 'listenTo' configuration groups.");
		return false;
	}
	
//	if (!group->QueryGroup("connectTo"))
//	{
//		BLADE_ERROR("Multiplayer initialization failed. Missing 'connectTo' configuration group.");
//		return false;
//	}

	BLADE_TRACE("Setting NetworkManager callbacks.");

	G_NetworkManager.SetOnNewClientCallback(OnNewClient);
	G_NetworkManager.SetOnNewPacketCallback(OnNewPacket);
	G_NetworkManager.SetOnClientDisconnectCallback(OnClientDisconnect);

	group = group->GetGroupByName("listenTo");
	unsigned short port = atoi(group->GetPropertyByName("port"));
	G_NetworkManager.Listen(port);
	BLADE_TRACE("Listening...");


//	group = group->GetGroupByName("connectTo");
//	if (group)
//	{
//		for (int i = 0; i < group->CountGroups(); ++i)
//		{
//			group = group->GetGroupByIndex(i);
//
//			std::string ip{ group->GetPropertyByName("ip") };
//			port = atoi(group->GetPropertyByName("port"));
//
//			G_NetworkManager.Connect(ip, port);
//		}
//	}

	return true;
}
