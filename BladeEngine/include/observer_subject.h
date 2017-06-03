#ifndef BLADE_OBSERVER_SUBJECT_H_
#define BLADE_OBSERVER_SUBJECT_H_
#include "observer.h"
#include <vector>
#include <map>
#include "types.h"

namespace Blade
{
	class ObserverSubject
	{
	private:
		// Listener registration
		std::map<std::string, std::vector<Observer*>> m_MessageListeners;

	public:
		ObserverSubject() = default;

		virtual ~ObserverSubject();

		// Register an observer for a particular type of message
		void RegisterObserver(const std::string& msg, Observer* o) noexcept;

		// De-register an observer
		void UnregisterObserver(const std::string& msg, Observer* o) noexcept;

		// Broadcast a message to any listeners
		void BroadcastMessage(const MessageContainer<std::string>& msg) const noexcept;
	};
}

#endif //BLADE_OBSERVER_SUBJECT_H_
