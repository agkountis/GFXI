#include "network_manager.h"
#include <iostream>
#include "trace.h"
#include "socket.h"
#include <vector>
#include "serialization_utils.h"

namespace Blade
{
	using namespace SerializationUtils;

	void NetworkManager::ConnectionAcceptorThreadMain(const unsigned short port)
	{
		Socket socket;

		BLADE_TRACE("Opening listening socket. Port: " + std::to_string(port));
		BLADE_TRACE("Listening...");
		if (!socket.Listen(port))
		{
			return;
		}

		while (!m_Terminating)
		{
			ConnectionInfo connectionInfo;
			Socket clientSocket{ socket.Accept(&connectionInfo) };

			if(m_Connections[std::get<unsigned long>(connectionInfo.ip)])
			{
				BLADE_TRACE("Connection already established. Aborting");
				return;
			}

			if (clientSocket.IsValid())
			{
				BLADE_TRACE("Accepting connection!");
				{
					std::lock_guard<std::mutex> lock{ m_Mutex };

					m_Connections[std::get<unsigned long>(connectionInfo.ip)] = std::make_unique<Socket>(std::move(clientSocket));

					BLADE_TRACE("Connection count: " + std::to_string(m_Connections.size()));
				}

				unsigned long id{ std::get<unsigned long>(connectionInfo.ip) };
				std::thread clientThread{ [id, this]() { ReceiveThreadMain(id); } };

				m_Threads.push_back(std::move(clientThread));

				if (m_OnNewClient)
				{
					m_OnNewClient(connectionInfo);
				}
			}
		}
	}

	void NetworkManager::ConnectThreadMain(const std::string& host, const unsigned short port)
	{
		int reconnectionAttempts{ 30 };

		Socket connectionSocket;

		BLADE_TRACE("Connecting to host: " + host + " Port:" + std::to_string(port));

		while (reconnectionAttempts && !m_Terminating)
		{
			ConnectionInfo connectionInfo;

			if (connectionSocket.Connect(host, port, &connectionInfo))
			{
				if (m_Connections[std::get<unsigned long>(connectionInfo.ip)])
				{
					BLADE_TRACE("Connection already established. Aborting");
					return;
				}

				BLADE_TRACE("Connection successful!");

				{
					std::lock_guard<std::mutex> lock{ m_Mutex };

					m_Connections[std::get<unsigned long>(connectionInfo.ip)] = std::make_unique<Socket>(std::move(connectionSocket));

					BLADE_TRACE("Connection count: " + std::to_string(m_Connections.size()));
				}

				unsigned long id{ std::get<unsigned long>(connectionInfo.ip) };

				std::thread clientThread{ [id, this]() { ReceiveThreadMain(id); } };

				m_Threads.push_back(std::move(clientThread));

				if (m_OnNewClient)
				{
					m_OnNewClient(connectionInfo);
				}

				return;
			}

			using namespace std::chrono_literals;
			std::this_thread::sleep_for(10s);

			--reconnectionAttempts;
		}

		BLADE_ERROR("Reconnection attempts depleted");
		BLADE_ERROR("Failed to connect! Host: " + host + " Port: " + std::to_string(port));
	}

	void NetworkManager::ReceiveThreadMain(const unsigned long idx)
	{
		int receivedBytes{ 0 };
		Byte buffer[1024];

		std::vector<Byte> accumulationBuffer;

		// Start receiving bytes untill we get an invalid value.
		while ((receivedBytes = m_Connections[idx]->Receive(buffer, sizeof buffer)) > 0)
		{
			accumulationBuffer.insert(accumulationBuffer.end(), buffer, buffer + receivedBytes);

			int packetSize{ 0 };

			int size = accumulationBuffer.size();

			while (size >= sizeof(int) && size >= (Unpack(accumulationBuffer, 0, packetSize) , packetSize))
			{
				std::vector<Byte> buff;
				buff.insert(buff.end(), accumulationBuffer.begin(), accumulationBuffer.begin() + packetSize);

				accumulationBuffer.erase(accumulationBuffer.begin(), accumulationBuffer.begin() + packetSize);

				size = accumulationBuffer.size();

				m_OnNewPacket(std::move(buff));
			}
		}

		BLADE_ERROR("Closing connection socket.");

		if (!m_Terminating)
		{
			BLADE_ERROR("Connection terminated by client.");
			if (m_OnClientDisconnect)
			{
				m_OnClientDisconnect();
			}

			auto it = m_Connections.cbegin();
			while (it != m_Connections.cend())
			{
				const auto& entry = *it;
				if (entry.first == idx)
				{
					it = m_Connections.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
		else
		{
			BLADE_TRACE("Application terminating. Closing connections.");
		}

		BLADE_TRACE("Connection count: " + std::to_string(m_Connections.size()));
	}

	void NetworkManager::SendThreadMain()
	{
		while (!m_Terminating)
		{
			std::shared_ptr<NetworkMessage> message{ nullptr };

			{
				std::lock_guard<std::mutex> lock{ m_Mutex };

				if (!m_MessageQueue.empty())
				{
					message = m_MessageQueue.front();

					m_MessageQueue.pop();
				}
			}

			if (message)
			{
				SendObject(message);
			}
		}

		BLADE_TRACE("Sending Thread terminating.");
	}

	NetworkManager::~NetworkManager()
	{
		m_Terminating = true;

		for (auto& entry : m_Connections)
		{
			entry.second->Close();
		}

		for (auto& thread : m_Threads)
		{
			if (thread.joinable())
			{
				thread.join();
			}
		}

		std::lock_guard<std::mutex> lock{ m_Mutex };

		for (int i = 0; i < m_MessageQueue.size(); ++i)
		{
			m_MessageQueue.pop();
		}

#ifdef WIN32
		WSACleanup();
#endif
	}

	bool NetworkManager::Initialize() noexcept
	{
#ifdef WIN32
		WSADATA wsaData;

		BLADE_TRACE("Initializing Windows sockets (WSA).");

		int res{ WSAStartup(MAKEWORD(2, 2), &wsaData) };

		if (res)
		{
			BLADE_ERROR("WSAStartup failed! Error: " + std::to_string(res));
			return false;
		}

		BLADE_TRACE("Windows socket initialization successful!");
#endif

		std::thread sendThread{ [this]() { SendThreadMain(); } };

		m_Threads.push_back(std::move(sendThread));

		return true;
	}

	void NetworkManager::Listen(const unsigned short port) noexcept
	{
		BLADE_TRACE("Starting connection listening thread.");

		std::thread listeningThread{ [this, port]() { ConnectionAcceptorThreadMain(port); } };

		listeningThread.detach();
	}

	void NetworkManager::Connect(const std::string& host, const unsigned short port) noexcept
	{
		std::thread connectionThread{ [this, host, port]() { ConnectThreadMain(host, port); } };

		m_Threads.push_back(std::move(connectionThread));
	}


	void NetworkManager::QueueMessage(const std::shared_ptr<NetworkMessage>& message) noexcept
	{
		std::lock_guard<std::mutex> lock{ m_Mutex };
		m_MessageQueue.push(message);
	}

	void NetworkManager::SendObject(const std::shared_ptr<NetworkMessage>& object) noexcept
	{
		auto data = object->Serialize();

		if (object->GetRecipientId() == RECIPIENT_ID_BROADCAST)
		{
			for (const auto& entry : m_Connections)
			{
				entry.second->Send(data.data(), data.size());
			}
		}
		else
		{
			auto& socket = m_Connections[object->GetRecipientId()];

			if (socket)
			{
				socket->Send(data.data(), data.size());
			}
			else
			{
				BLADE_ERROR("Recipient with id" + std::to_string(object->GetRecipientId()) + " is not a valid connection.");
			}
		}
	}

	size_t NetworkManager::GetConnectionCount() noexcept
	{
		std::lock_guard<std::mutex> lock{ m_Mutex };

		return m_Connections.size();
	}

	void NetworkManager::SetOnNewPacketCallback(const OnNewPacketCallback& callback) noexcept
	{
		m_OnNewPacket = callback;
	}

	void NetworkManager::SetOnNewClientCallback(const OnNewClientCallback& callback) noexcept
	{
		m_OnNewClient = callback;
	}

	void NetworkManager::SetOnClientDisconnectCallback(const OnClientDisconnectCallback& callback) noexcept
	{
		m_OnClientDisconnect = callback;
	}
}
