#ifndef COMMAND_MESSAGE_H_
#define COMMAND_MESSAGE_H_
#include "network_message.h"

class CommandMessage : public Blade::NetworkMessage
{
private:
	int m_PlayerID;
	void* m_Data;
public:
	explicit CommandMessage(int playerID,int messageType, long recipientId, void* data = nullptr);

	std::vector<Blade::Byte> Serialize() noexcept override;
};

#endif //COMMAND_MESSAGE_H_