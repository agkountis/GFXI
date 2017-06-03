#ifndef BLADE_MESSAGE_H_
#define BLADE_MESSAGE_H_

namespace Blade
{
	template<typename T>
	class Message
	{
	private:
		T m_Type;

	public:
		explicit Message(T&& type) : m_Type{ type }
		{
		}

		virtual ~Message() = default;

		const T& GetMessageType() const noexcept
		{
			return m_Type;
		}
	};
}

#endif //GLACIER_MESSAGE_H_
