#ifndef BLADE_SOCKET_H_
#define BLADE_SOCKET_H_

#ifdef WIN32
#include <winsock2.h>
#endif

#include <string>

namespace Blade
{
#ifdef WIN32
	using SocketHandle = SOCKET;
#else
	using SocketHandle = int;
#define INVALID_SOCKET -1
#endif

	class Socket
	{
	private:
		SocketHandle m_Handle{ INVALID_SOCKET };

	public:
		Socket();

		Socket(SocketHandle handle);

	   ~Socket();

		Socket(const Socket& other) = delete;

		Socket(Socket&& other) noexcept;

		bool Connect(const std::string& host, unsigned short port) const noexcept;

		bool Listen(unsigned short port, int maxQueueSize = 8) const noexcept;

		void Close() noexcept;

		Socket Accept() const noexcept;

		bool IsValid() const noexcept;

		SocketHandle GetHandle() const noexcept;

		void SetHandle(SocketHandle handle) noexcept;

		bool Send(const char* buffer, int size) const noexcept;

		int Receive(char* buffer, int size) const noexcept;
	};
}

#endif //BLADE_SOCKET_H_