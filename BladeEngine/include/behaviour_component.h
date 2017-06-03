#ifndef BLADE_BEHAVIOUR_COMPONENT_H_
#define BLADE_BEHAVIOUR_COMPONENT_H_
#include "component.h"

namespace Blade
{
	/*
		* \brief BehaviourComponent class of the engine. All the components of the engine
	 * that needs to perform and action derive from this class. BehaviourComponent inherits from the Component class so it can
	 * register and receive specific messages.
	*/
	class BehaviourComponent : public Component
	{
	public:
		/**
		* \brief Performs setup actions after the BehaviourComponent's creation
		*/
		virtual void Setup() noexcept = 0;


		/**
		* \brief Performs actions before the BehaviourComponent is destroyed.
		*/
		virtual void Teardown() noexcept = 0;

		/**
		* \brief Updates the Component on each frame.
		* \param dt The time elapsed from the previous frame of the Application.
		* \param time The elapsed time since the start of the Application.
		*/
		virtual void Update(const float dt, const long time = 0) noexcept = 0;
	};
}

#endif