#ifndef BLADE_MESSAGE_H_
#define BLADE_MESSAGE_H_

namespace Blade
{
	/*
	\brief Message structure used by the engine.
	\details The Message class is generic. 
	*/
	template<typename T>
	class Message
	{
	private:
		/*
		\brief Message type
		*/
		T m_Type;

	public:
		explicit Message(T&& type) : m_Type{ type }
		{
		}

		virtual ~Message() = default;
		/*
		\brief Return the type of the message
		\return The message type
		*/
		const T& GetType() const noexcept
		{
			return m_Type;
		}
	};
}

#endif //GLACIER_MESSAGE_H_
