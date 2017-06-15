#ifndef MULTIPLAYER_H_
#define MULTIPLAYER_H_
#include <vector>
#include "types.h"
#include "socket.h"
#include "player_commands.h"

namespace Multiplayer
{

	void OnNewClient(Blade::ConnectionInfo connectionInfo);

	void OnClientDisconnect();

	void OnNewPacket(std::vector<Blade::Byte> packet);
};

#endif //MULTIPLAYER_H_
