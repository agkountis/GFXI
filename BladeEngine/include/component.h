#ifndef BLADE_COMPONENT_H_
#define BLADE_COMPONENT_H_
#include <string>
#include "observer.h"

namespace Blade
{
	class Entity;

	/**
	 * \brief Base Component class of the engine. All the components of the engine
	 * derive from this class. Compoment inherits from the Observer class so it can 
	 * register and receive specific messages.
	 */
	class Component : public Observer
	{
	private:
		/**
		 * \brief The type of the component defined as a string.
		 */
		const std::string m_Type;

		/**
		 * \brief The Entity that the component is attached to.
		 */
		Entity* p_Parent{ nullptr };

		/**
		 * \brief A unique identifier for the Component.
		 */
		static int m_Id;

	public:
		/**
		 * \brief Component constructor.
		 * \param type The type of the Component as a string.
		 * \param parent The Entity the Component will be attached to.
		 */
		Component(const std::string& type, Entity* parent);

		Component(const Component& other) = delete;

		Component& operator=(const Component& other) = delete;

		/**
		 * \brief Default destructor of the Component.
		 */
		virtual ~Component();

		/**
		 * \brief Returns the type of the Component.
		 * \return The type of the Component.
		 */
		const std::string& GetType() const noexcept;

		/**
		 * \brief Returns the Entity that the Component is attached to.
		 * \return The Entity that the Component is attached to.
		 */
		Entity* GetParent() const noexcept;

		/**
		 * \brief Returns the unique Component ID.
		 * \return The unique Component ID.
		 */
		static int GetId() noexcept;

		/**
		 * \brief Performs setup actions after the Component's creation
		 */
		virtual void Setup() noexcept = 0;

		/**
		 * \brief Updates the Component on each frame.
		 * \param dt The time elapsed from the previous frame of the application.
		 * \param time The elapsed time since the start of the application.
		 */
		virtual void Update(float dt, long time = 0) noexcept = 0;

		/**
		 * \brief Performs actions before the Component is destroyed.
		 */
		virtual void Teardown() noexcept = 0;

		/**
		 * \brief Broadcasts the recieved message to the current active Scene
		 * through the SceneManager.
		 * \param msg The message received.
		 */
		void OnMessage(const MessageContainer& msg) override;
	};
}

#endif //BLADE_COMPONENT_H_
