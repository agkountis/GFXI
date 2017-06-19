#ifndef BLADE_INPUT_COMPONENT_H_
#define BLADE_INPUT_COMPONENT_H_
#include "behaviour_component.h"

namespace Blade
{
	/**
	 * \brief InputComponent class of the engine. All the input components of the engine 
	 * derive from this abstractClass.
	 */
	class InputComponent : public BehaviourComponent
	{
	protected:
		bool m_Online;

	public:
		/**
		 * \brief Input component constructor.
		 * \param type The type of the InputComponent as a string
		 * \param parent The entity the InputComponent will be attached to.
		 */
		explicit InputComponent(const std::string& type, Entity* parent, bool online = false);

		InputComponent(const InputComponent& other) = delete;

		InputComponent& operator=(const InputComponent& other) = delete;

		virtual ~InputComponent();

		/**
		 * \brief Updates the InputComponent.
		 * \param dt The delta time of the application.
		 * \param time The time in milliseconds.
		 */
		void Update(const float dt, const long time = 0) noexcept override = 0;

		/**
		 * \brief Sets up the InputComponent.
		 * \remarks Shoulds be called after component instantiation.
		 */
		void Setup() noexcept override = 0;

		/**
		 * \brief Performs pre destruction actions.
		 * \remarks Should be called before component destruction.
		 */
		void Teardown() noexcept override = 0;
			
	};

}

#endif