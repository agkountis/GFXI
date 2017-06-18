#ifndef BLADE_NETWORK_MANAGER_H_
#define BLADE_NETWORK_MANAGER_H_
#include <map>
#include <mutex>
#include <vector>
#include <queue>
#include "network_message.h"
#include "socket.h"

namespace Blade
{
	using OnNewClientCallback = std::function<void(ConnectionInfo connectionInfo)>;

	using OnNewPacketCallback = std::function<void(std::vector<Byte>)>;

	using OnClientDisconnectCallback = std::function<void()>;

	using ConnectionMap = std::map<unsigned long, std::unique_ptr<Socket>>;

	using MessageQueue = std::queue<std::shared_ptr<NetworkMessage>>;

	/**
	\brief Network manager of the engine. Manages the listening, connection, sending and receiving to different
	multiple sockets.
	*/
	class NetworkManager
	{
	private:
		/**
		\brief Connection map that associate the unique id to a peer to a socket.
		*/
		ConnectionMap m_Connections;

		/**
		\brief Store the message queue.
		*/
		MessageQueue m_MessageQueue;

		/**
		\brief Vector of threads
		*/
		std::vector<std::thread> m_Threads;

		std::mutex m_Mutex;

		void ConnectionAcceptorThreadMain(const unsigned short port);

		void ConnectThreadMain(const std::string& host, const unsigned short port);

		/**
		\brief Receive thread main used by the threads to perform the receiving process.
		*/
		void ReceiveThreadMain(const unsigned long clientId);

		/**
		\brief Send thread main used by the threads to perform the sending process.
		*/
		void SendThreadMain();

		/**
		\brief Send a object to the network
		*/
		void SendObject(const std::shared_ptr<NetworkMessage>& object) noexcept;

		OnNewPacketCallback m_OnNewPacket;

		OnNewClientCallback m_OnNewClient;

		OnClientDisconnectCallback m_OnClientDisconnect;

		bool m_Terminating{ false };

	public:
		~NetworkManager();

		/**
		\brief Initialize the network manager
		*/
		bool Initialize() noexcept;

		/**
		\brief Listen to an assigned port using the provided callback.
		\details The listening process is being process on its own thread.
		\param port the port to listen to
		*/
		void Listen(const unsigned short port) noexcept;

		/**
		\brief Connect to a host using the provided callback
		\details The connection process is being process on its own thread.
		\param host The IP address of the host
		\param port The port number 
		*/
		void Connect(const std::string& host, const unsigned short port) noexcept;

		/**
		\brief Queue a new message
		\param message The message to queue. 
		*/
		void QueueMessage(const std::shared_ptr<NetworkMessage>& message) noexcept;

		/**
		\brief Getters of the connection count.
		\return the number of open connections.
		*/
		size_t GetConnectionCount() noexcept;

		/**
		\brief Set the callback that execute when a new packet is received.
		\param callback The on new packet callback to set.
		*/
		void SetOnNewPacketCallback(const OnNewPacketCallback& callback) noexcept;

		/**
		\brief Set the callback that execute when a new client is connected.
		\param callback The on new client callback to set.
		*/
		void SetOnNewClientCallback(const OnNewClientCallback& callback) noexcept;

		/**
		\brief Set the callback that execute when a client is disconnected.
		\param callback The on client disconnect callback to set.
		*/
		void SetOnClientDisconnectCallback(const OnClientDisconnectCallback& callback) noexcept;
	};
}

#endif //BLADE_NETWORK_MANAGER_H_
