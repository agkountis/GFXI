#include "command_message.h"
#include "serialization_utils.h"
#include "network_message_types.h"

using namespace Blade;
using namespace SerializationUtils;

CommandMessage::CommandMessage(int value, int messageType, long recipientId, void* data) :
	NetworkMessage{ std::move(messageType),  recipientId },
	m_PlayerID{ value },
	m_Data{data}
{
}

std::vector<Byte> CommandMessage::Serialize() noexcept
{
	std::vector<Byte> serializedData;
	int dataSize{ 0 };
	Vec3f stickRot;
	Vec3f stickMov;
	if (m_Data)
	{
		dataSize = sizeof m_PlayerID + 6 * sizeof(float);

		Byte* buff = reinterpret_cast<Byte*>(m_Data);

		stickRot.x = *reinterpret_cast<float*>(buff);
		buff += sizeof(float);
		stickRot.y = *reinterpret_cast<float*>(buff);
		buff += sizeof(float);
		stickRot.z = *reinterpret_cast<float*>(buff);
		buff += sizeof(float);
		stickMov.x = *reinterpret_cast<float*>(buff);
		buff += sizeof(float);
		stickMov.y = *reinterpret_cast<float*>(buff);
		buff += sizeof(float);
		stickMov.z = *reinterpret_cast<float*>(buff);

	}
	else
	{
		dataSize = sizeof m_PlayerID;
	}

	int size = 2 * sizeof(int) + dataSize ;

	Pack(serializedData, size);
	
	int msgType = GetType();
	Pack(serializedData, msgType);

	Pack(serializedData, m_PlayerID);

	if (m_Data)
	{
		Pack(serializedData, stickRot);
	}



	return std::move(serializedData);
}
