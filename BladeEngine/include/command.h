#ifndef BLADE_COMMAND_H_
#define BLADE_COMMAND_H_
#include "entity.h"

namespace Blade
{
	/*
	\brief Command pattern class.Encapsulate a request as an object, thereby letting users parameterize
	clients with different requests,queue or log requests, and support undo able operations.
	*/
	class Command
	{
	protected:
		bool m_Online;

	public:
		Command(bool online = false) :m_Online{ online } {}

		virtual ~Command() = default;

		/*
		\brief Execute method of the command.
		\param entity the entity that performs the action
		\param dt the delta time.
		*/
		virtual void Execute(Entity* entity, const float dt) = 0;

	
	};

}

#endif // !BLADE_COMMAND_H_
