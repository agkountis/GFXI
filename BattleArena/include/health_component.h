#ifndef HEALTH_COMPONENT_H_
#define HEALTH_COMPONENT_H_
#include "behaviour_component.h"
#include "timer.h"
#include "health_bar.h"

class HealthComponent : public Blade::BehaviourComponent
{
private:
	const int m_InitialValue{ 10 };

	const int m_CollisionTimeOffset{ 20 };

	const int m_Damage{ 1 };

	int m_HealthValue{ m_InitialValue };

	Blade::Timer m_Timer;

	HealthBar* m_pListenerBar{ nullptr };

public:
	HealthComponent(Blade::Entity* parent);

	void Update(const float dt, const long time = 0) noexcept override;

	/**
	 * \brief Performs setup actions after the BehaviourComponent's creation
	 */
	void Setup() noexcept override;

	/**
	 * \brief Performs actions before the BehaviourComponent is destroyed.
	 */
	void Teardown() noexcept override;

	/**
	 * \brief Called when collision with other Entity occurs.
	 * \param other Entity that collided with parent of this behaviour
	 */
	void OnCollision(Blade::Entity* other) noexcept override;

	/**
	 * \brief Returns current health value
	 * \return heatlh value
	 */
	int GetHealthValue() const noexcept;


	void SetListenerBar(HealthBar* healthBar);
};
#endif

