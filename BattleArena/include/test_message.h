#ifndef TEST_MESSAGE_H_
#define TEST_MESSAGE_H_
#include "network_message.h"

class TestMessage : public Blade::NetworkMessage
{
private:
	int m_Test;

public:
	explicit TestMessage(int value);

	std::vector<Blade::Byte> Serialize() noexcept override;
};

#endif //TEST_MESSAGE_H_