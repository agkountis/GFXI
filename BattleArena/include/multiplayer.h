#ifndef MULTIPLAYER_H_
#define MULTIPLAYER_H_
#include <vector>
#include "types.h"
#include "socket.h"

class Multiplayer
{
private:
	static void OnNewClient(Blade::ConnectionInfo connectionInfo);

	static void OnClientDisconnect();

	static void OnNewPacket(std::vector<Blade::Byte> packet);

public:
	static bool Initialize(const std::string& networkConfigFileName) noexcept;
};

#endif //MULTIPLAYER_H_
