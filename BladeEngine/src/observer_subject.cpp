#include "observer_subject.h"

namespace Blade
{
	ObserverSubject::~ObserverSubject()
	{
	}

	void ObserverSubject::RegisterObserver(const std::string& msg, Observer* o) noexcept
	{
		auto it{ m_MessageListeners.find(msg) };

		if (it == m_MessageListeners.end())
		{
			m_MessageListeners[msg] = std::vector<Observer*>{ o };
		}
		else
		{
			m_MessageListeners[msg].push_back(o);
		}
	}

	void ObserverSubject::UnregisterObserver(const std::string& msg, Observer* o) noexcept
	{
		auto map_it{ m_MessageListeners.find(msg) };

		if (map_it != m_MessageListeners.end())
		{
			auto& observers{ map_it->second };

			auto it{ std::find(observers.begin(), observers.end(), o) };

			if (it != observers.end())
			{
				observers.erase(it);
			}
		}
	}

	void ObserverSubject::BroadcastMessage(const MessageContainer<std::string>& msg) const noexcept
	{
		// Dispatch message to all registered listeners
		auto map_it{ m_MessageListeners.find(msg.Get()->GetType()) };

		// If we have registered listeners for this message
		if (map_it != m_MessageListeners.end())
		{
			auto& observers{ map_it->second };

			for (auto observer : observers)
			{
				observer->OnMessage(msg);
			}
		}
	}
}
