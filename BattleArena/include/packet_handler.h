#ifndef PACKET_HANDLER_H_
#define PACKET_HANDLER_H_
#include <vector>
#include "types.h"

void OnNewClient();

void OnClientDisconnect();

void OnNewPacket(std::vector<Blade::Byte> packet);

#endif //PACKET_HANDLER_H_
