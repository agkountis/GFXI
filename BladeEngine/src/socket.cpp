#include "socket.h"
#include <cassert>
#include <iostream>
#include "trace.h"

namespace Blade
{
	Socket::Socket()
	{
		m_Handle = socket(AF_INET, SOCK_STREAM, 0);
		assert(m_Handle != INVALID_SOCKET);
	}

	Socket::Socket(SocketHandle handle) : m_Handle{ handle }
	{
	}

	Socket::~Socket()
	{
		Close();
	}

	Socket::Socket(Socket&& other) noexcept
	{
		m_Handle = other.GetHandle();
		other.SetHandle(INVALID_SOCKET);
	}

	bool Socket::Connect(const std::string& host, unsigned short port) const noexcept
	{
		hostent* hostAddr{ gethostbyname(host.c_str()) };

		if (!hostAddr)
		{
			BLADE_ERROR("Failed to connect. Invalid address.");
			return false;
		}

		sockaddr_in address{};
		address.sin_family = AF_INET;
		address.sin_port = htons(port);
		address.sin_addr.s_addr = *reinterpret_cast<unsigned long*>(hostAddr->h_addr);

		if (connect(m_Handle, reinterpret_cast<sockaddr*>(&address), sizeof address) == -1)
		{
			BLADE_ERROR("Failed to connect.");
			return false;
		}

		int flag = 1;
		setsockopt(m_Handle, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&flag), sizeof flag);

		return true;
	}

	bool Socket::Listen(unsigned short port, int maxQueueSize) const noexcept
	{
		sockaddr_in address{};
		address.sin_family = AF_INET;
		address.sin_port = htons(port);
		address.sin_addr.s_addr = htonl(INADDR_ANY);

		if (bind(m_Handle, reinterpret_cast<sockaddr*>(&address), sizeof address) == -1)
		{
			BLADE_ERROR("Failed to bind socket to port " + std::to_string(port));
			return false;
		}

		listen(m_Handle, maxQueueSize);

		return true;
	}

	void Socket::Close() noexcept
	{
		if (IsValid())
		{
			shutdown(m_Handle, SD_SEND);
			closesocket(m_Handle);
			m_Handle = INVALID_SOCKET;
		}
	}

	Socket Socket::Accept() const noexcept
	{
		Socket socket{ accept(m_Handle, nullptr, nullptr) };

		if (!socket.IsValid())
		{
			BLADE_ERROR("Failed to accept connection.");
		}

		int flag = 1;
		setsockopt(socket.GetHandle(), IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&flag), sizeof flag);

		return std::move(socket);
	}

	bool Socket::IsValid() const noexcept
	{
		return m_Handle != INVALID_SOCKET;
	}

	SocketHandle Socket::GetHandle() const noexcept
	{
		return m_Handle;
	}

	void Socket::SetHandle(SocketHandle handle) noexcept
	{
		m_Handle = handle;
	}

	bool Socket::Send(const char* buffer, int size) const noexcept
	{
		if (send(m_Handle, buffer, size, 0) == -1)
		{
			return false;
		}

		return true;
	}

	int Socket::Receive(char* buffer, int size) const noexcept
	{
		return recv(m_Handle, buffer, size, 0);
	}
}
