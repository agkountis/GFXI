#ifndef BLADE_NETWORK_MESSAGE_H_
#define BLADE_NETWORK_MESSAGE_H_
#include "serializable.h"

namespace Blade
{

	class NetworkMessage : public Message<int>, public Serializable
	{
	public:
		explicit NetworkMessage(int&& type) : Message<int>{ std::move(type) }
		{}
	};
}

#endif //BLADE_NETWORK_MESSAGE_H_
