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

	using ConnectionMap = std::map<long, std::unique_ptr<Socket>>;

	using MessageQueue = std::queue<std::shared_ptr<NetworkMessage>>;

	class NetworkManager
	{
	private:
		ConnectionMap m_Connections;

		MessageQueue m_MessageQueue;

		std::vector<std::thread> m_Threads;

		std::mutex m_Mutex;

		void ConnectionAcceptorThreadMain(const unsigned short port);

		void ConnectThreadMain(const std::string& host, const unsigned short port);

		void ReceiveThreadMain(const long clientId);

		void SendThreadMain();

		void SendObject(const std::shared_ptr<NetworkMessage>& object) noexcept;

		OnNewPacketCallback m_OnNewPacket;

		OnNewClientCallback m_OnNewClient;

		OnClientDisconnectCallback m_OnClientDisconnect;

		bool m_Terminating{ false };

	public:
		~NetworkManager();

		bool Initialize() noexcept;

		void Listen(const unsigned short port) noexcept;

		void Connect(const std::string& host, const unsigned short port) noexcept;

		void QueueMessage(const std::shared_ptr<NetworkMessage>& message) noexcept;

		size_t GetConnectionCount() noexcept;

		void SetOnNewPacketCallback(const OnNewPacketCallback& callback) noexcept;

		void SetOnNewClientCallback(const OnNewClientCallback& callback) noexcept;

		void SetOnClientDisconnectCallback(const OnClientDisconnectCallback& callback) noexcept;
	};
}

#endif //BLADE_NETWORK_MANAGER_H_
