#ifndef BLADE_HEALTH_COMPONENT_H_
#define BLADE_HEALTH_COMPONENT_H_
#include "behaviour_component.h"
#include "timer.h"

class HealthComponent : public Blade::BehaviourComponent
{

private:
	const int m_InitialValue = 10;
	const int m_CollisionTimeOffset = 20;
	const int m_Damage = 1;
	int m_HealthValue{ m_InitialValue };

	Blade::Timer m_Timer;

public:
	HealthComponent(Blade:: Entity* parent);
	~HealthComponent();


	void Update(const float dt, const long time = 0) noexcept;

	/**
	* \brief Performs setup actions after the BehaviourComponent's creation
	*/
	void Setup() noexcept;

	/**
	* \brief Performs actions before the BehaviourComponent is destroyed.
	*/
	void Teardown() noexcept;


	/**
	* \brief Called when collision with other Entity occurs.
	* \param other Entity that collided with parent of this behaviour
	*/
	void OnCollision(Blade::Entity* other) noexcept;


	/**
	* \brief Returns current health value
	* \return heatlh value
	*/
	int GetHealthValue();
};
#endif

