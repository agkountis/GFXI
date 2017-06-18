#ifndef BLADE_SOCKET_H_
#define BLADE_SOCKET_H_

#ifdef WIN32
#include <winsock2.h>
#endif

#include <string>
#include <tuple>

namespace Blade
{
#ifdef WIN32
	using SocketHandle = SOCKET;
#else
	using SocketHandle = int;
#define INVALID_SOCKET -1
#endif

	/**
	\brief Connection information.
	*/
	struct ConnectionInfo
	{
		/**
		\brief Map that stores the IP address both in string form and using long.
		*/
		std::tuple<std::string, unsigned long> ip;

		/**
		\brief Port of the connection.
		*/
		unsigned short port;
	};

	/**
	\brief TCP Socket of the engine.
	*/
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

		/**
		\brief Connect the socket and stores back theConnectionInfo
		\param host	The IP address to connect to.
		\param port The port number 
		\param connection_info A connection info pointer to store back the information of the connection, only 
		if that succeeded.
		\return TRUE if the connection happened, FALSE otherwise.
		*/
		bool Connect(const std::string& host, unsigned short port, ConnectionInfo* connection_info = nullptr) const noexcept;

		/**
		\brief List to the selected port 
		\param port The port to listen at
		\param maxQueueSize The max queue size
		\return TRUE if somebody connected, FALSE otherwise
		*/
		bool Listen(unsigned short port, int maxQueueSize = 8) const noexcept;

		/**
		\brief Close the socket and the connection.
		*/
		void Close() noexcept;

		/**
		\brief Accept the connection.
		\param connectionInfo The connection to accept.
		\return The socket created after the accept.
		*/
		Socket Accept(ConnectionInfo* connectionInfo = nullptr) const noexcept;

		/**
		\brief Check if the socket is valid
		\return TRUE if is valid, FALSE otherwise.
		*/
		bool IsValid() const noexcept;


		/**
		\brief Getter of the handle
		\return The socket handle.
		*/
		SocketHandle GetHandle() const noexcept;

		/**
		\brief Setter of the handle.
		\param handle The socket handle to set.s
		*/
		void SetHandle(SocketHandle handle) noexcept;

		/**
		\brief Send data to this socket.
		\param buffer Pointer to the buffer that needs to be sent.
		\param size The size of the buffer that needs to be sent.
		\return TRUE if the sent happened, FALSE otherwise.
		*/
		bool Send(const char* buffer, int size) const noexcept;

		/**
		\brief Receive data from the network.
		\param buffer The pointer the buffer where to store the coming data.
		\param size The dimension of the buffer 
		\return int the number of bytes read.
		*/
		int Receive(char* buffer, int size) const noexcept;
	};
}

#endif //BLADE_SOCKET_H_
