#include "test_message.h"
#include "serialization_utils.h"
#include "network_message_types.h"

using namespace Blade;
using namespace SerializationUtils;

TestMessage::TestMessage(int value) :
	NetworkMessage{ BA_TEST_MESSAGE },
	m_Test{ value }
{
}

std::vector<Byte> TestMessage::Serialize() noexcept
{
	std::vector<Byte> serializedData;

	int size{ 2 * sizeof(int) + sizeof m_Test };

	Pack(serializedData, size);
	
	int msgType = GetType();
	Pack(serializedData, msgType);

	Pack(serializedData, m_Test);

	return std::move(serializedData);
}
