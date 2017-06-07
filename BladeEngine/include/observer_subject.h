#ifndef BLADE_OBSERVER_SUBJECT_H_
#define BLADE_OBSERVER_SUBJECT_H_
#include "observer.h"
#include <vector>
#include <map>
#include "types.h"

namespace Blade
{
	/*
	\brief ObjeserverSubject implemented by the engine
	\details The engine provides observer pattern interface
	*/
	class ObserverSubject
	{
	private:
		/*
		\brief Listener registration
		*/
		std::map<std::string, std::vector<Observer*>> m_MessageListeners;

	public:
		ObserverSubject() = default;

		virtual ~ObserverSubject();

		// Register an observer for a particular type of message

		/*
		\brief Register an observer for a particular type of message
		\param msg the message type
		\param o the observer to register. 
		*/
		void RegisterObserver(const std::string& msg, Observer* o) noexcept;

		/*
		\brief Unregister an observer for a particular type of message
		\param msg the message type
		\param o the observer to unregister.
		*/
		void UnregisterObserver(const std::string& msg, Observer* o) noexcept;

		/*
		\brief Broadcast a message to any listeners
		\param msg the message to broadcast.
		*/
		void BroadcastMessage(const MessageContainer<std::string>& msg) const noexcept;
	};
}

#endif //BLADE_OBSERVER_SUBJECT_H_
