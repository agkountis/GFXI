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
	using OnNewClientCallback = std::function<void()>;

	using OnNewPacketCallback = std::function<void(std::vector<Byte>)>;

	using OnClientDisconnectCallback = std::function<void()>;

	class NetworkManager
	{
	private:
		std::map<int, std::unique_ptr<Socket>> m_Connections;

		std::mutex m_Mutex;

		std::queue<std::shared_ptr<NetworkMessage>> m_MessageQueue;

		std::vector<std::thread> m_Threads;

		void ConnectionAcceptorThreadMain(unsigned short port);

		void ConnectThreadMain(const std::string& host, unsigned short port);

		void ReceiveThreadMain(const int clientId);

		void SendThreadMain();

		void SendObject(const std::shared_ptr<NetworkMessage>& object) noexcept;

		OnNewPacketCallback m_OnNewPacket;

		OnNewClientCallback m_OnNewClient;

		OnClientDisconnectCallback m_OnClientDisconnect;

		bool m_Terminating{ false };

	public:
		~NetworkManager();

		bool Initialize() noexcept;

		void Listen(unsigned short port) noexcept;

		void Connect(const std::string& host, unsigned short port) noexcept;

		void QueueMessage(const std::shared_ptr<NetworkMessage>& message) noexcept;

		size_t GetConnectionCount() noexcept;

		void SetOnNewPacketCallback(const OnNewPacketCallback& callback) noexcept;

		void SetOnNewClientCallback(const OnNewClientCallback& callback) noexcept;

		void SetOnClientDisconnectCallback(const OnClientDisconnectCallback& callback) noexcept;
	};
}

#endif //BLADE_NETWORK_MANAGER_H_
