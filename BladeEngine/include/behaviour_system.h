#ifndef BLADE_BEHAVIOUR_SYSTEM_H_
#define BLADE_BEHAVIOUR_SYSTEM_H_
#include "system.h"
#include <map>
#include "behaviour_component.h"
#include <vector>
namespace Blade
{
	/**
	* \brief A System responsible to process and manage the BehaviourComponents
	* by calling the Update method on every component.
	*/
	class BehaviourSystem : public System 
	{
	private:
		/**
		* \brief The registered BehaviourComponents.
		*/
		std::map<std::string, BehaviourComponent*> m_BehaviourComponents;	

	public:
		/**
		* \brief Processes the BehaviourComponent.
		* \param deltaTime The time elapsed from the previous frame of the application.
		*/
		void Process(float deltaTime=.0f, long time=0) noexcept override;
		/**
		* \brief Initializes the BehaviourSystem.
		* \return TRUE if initialization is successful, FALSE otherwise.
		*/
		bool Initialize() noexcept override;
		/**
		* \brief Registers the specified BehaviourComponent to the BehaviourSystem.
		* \param behaviourComponent The BehaviourComponent to be registered to the BehaviourSystem for processing.
		*/
		void RegisterComponent(BehaviourComponent* behaviourComponent) noexcept;

		/**
		* \brief Unregisters a BehaviourComponent from the BehaviourSystem.
		* \param id The unique id of the BehaviourComponent to be unregistered.
		*/
		void UnregisterComponent(int id) noexcept;

		/**
		* \brief Setup all the BehaviourComponent that are currently registered with the  BehaviourSystem.
		*/
		virtual void Setup() noexcept;

		/**
		* \brief Teardown all the BehaviourComponent that are currently registered with the BehaviourSystem.
		*/
		virtual void Teardown() noexcept;

		/*
		\brief Function that returns a vector of all the behaviour component of a selected type
		\param the type of the component that you want to obtain
		\return the vector of components of the type requested.
		*/
		std::vector<BehaviourComponent*> GetBehaviourByType(const std::string type) const;
	};
}
#endif
