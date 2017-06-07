#ifndef BLADE_NETWORK_MESSAGE_H_
#define BLADE_NETWORK_MESSAGE_H_
#include "serializable.h"

namespace Blade
{
	static constexpr long RECIPIENT_ID_BROADCAST{ -1 };

	class NetworkMessage : public Message<int>, public Serializable
	{
	private:
		long m_RecipientId;

	public:
		explicit NetworkMessage(int&& type, long recipientId) :
			Message<int>{ std::move(type) },
			m_RecipientId{ recipientId }
		{
		}

		int GetRecipientId() const noexcept
		{
			return m_RecipientId;
		}
	};
}

#endif //BLADE_NETWORK_MESSAGE_H_
