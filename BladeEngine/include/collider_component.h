#ifndef BLADE_COLLIDER_COMPONENT_H_
#define BLADE_COLLIDER_COMPONENT_H_
#include "component.h"
#include "collider.h"
#include <memory>

#include "trace.h"
namespace Blade
{
	//Forward declaration
	class Entity;
	class BehaviourComponent;
	/*
	\brief ColliderComponent class of the engine is a component without behaviour
	*/
	class ColliderComponent : public Component
	{
	private:
		/*
		\brief Flag value to enable or disable collision response
		\details If it is false the collider will not take part on the collision 
		detection process.
		*/
		bool m_activeFlag{ true };

		/*
		\brief Unique pointer to the correspondent collider.
		*/
		std::unique_ptr<Collider> m_Collider;


		BehaviourComponent* m_pListenerBehaviour{ nullptr };

	//protected:
	


	public:

		ColliderComponent(Entity* parent, std::unique_ptr<Collider> collider);

		ColliderComponent(ColliderComponent&) = delete;

		ColliderComponent& operator=(ColliderComponent&) = delete;

		~ColliderComponent();

		/*
		\brief Setter to the collider
		\param collider the collider to set.
		*/
		void SetCollider(std::unique_ptr<Collider> collider) noexcept;

		/*
		\brief Getter to the collider
		\return Pointer to the correspondent collider
		*/
		Collider* GetCollider() const noexcept;

		/*
		\brief Getter of the collision response flag
		\return true if the collider component is active, false otherwise
		*/
		bool IsActive() const noexcept;

		/*
		\brief Setter for the flag to the collider flag.
		*/
		void SetCollisionResponseFlag(bool flag) noexcept;

		/*
		\brief Setter for collision listener behaviour
		*/
		void SetListener(BehaviourComponent* listener) noexcept;

		/*
		\brief Method used to notify BehaviourComponent listener about the collision
		\param entity that the collider collided with
		*/
		void NotifyCollisionListener(Entity* entity) noexcept;
	};
}
#endif 