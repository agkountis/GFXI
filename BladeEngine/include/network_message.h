#ifndef BLADE_NETWORK_MESSAGE_H_
#define BLADE_NETWORK_MESSAGE_H_
#include "serializable.h"

namespace Blade
{
	/**
	\brief Recipient ID board cast flag is used to broadcast a message to every peer 
	connected.
	*/
	static constexpr long RECIPIENT_ID_BROADCAST{ -1 };

	/**
	\brief Network message of the engine is a serializable message.
	*/
	class NetworkMessage : public Message<int>, public Serializable
	{
	private:
		/**
		\brief Recipient ID
		*/
		long m_RecipientId;

	public:

		/**
		\brief NetworkMessage constructor
		\param type The type of message to send
		\param recipientId The id of the receiver. 
		*/
		explicit NetworkMessage(int&& type, long recipientId) :
			Message<int>{ std::move(type) },
			m_RecipientId{ recipientId }
		{
		}

		/**
		\brief Getters of the recipient ID.
		\return The id of the recipient.
		*/
		int GetRecipientId() const noexcept
		{
			return m_RecipientId;
		}
	};
}

#endif //BLADE_NETWORK_MESSAGE_H_
