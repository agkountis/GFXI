#ifndef BLADE_MESSAGE_H_
#define BLADE_MESSAGE_H_
#include <string>

namespace Blade
{
	class Message
	{
	private:
		std::string m_Type;

	public:
		explicit Message(const std::string& type) : m_Type{ type }
		{
		}

		virtual ~Message();

		const std::string& get_message_type() const noexcept
		{
			return m_Type;
		}
	};
}

#endif //GLACIER_MESSAGE_H_
