#ifndef EXPLOSION_BEHAVIOUR_H_
#define EXPLOSION_BEHAVIOUR_H_
#include "behaviour_component.h"
#include "timer.h"

class ExplosionBehaviour : public Blade::BehaviourComponent
{
private:
	Blade::Timer m_Timer;
	float m_Lifetime{ 0 };
public:
	ExplosionBehaviour(Blade::Entity* entity,float lifetimeInSceconds);
	~ExplosionBehaviour();

	void Update(const float dt, const long time = 0) noexcept;

	/**
	* \brief Performs setup actions after the BehaviourComponent's creation
	*/
	void Setup() noexcept;

	/**
	* \brief Performs actions before the BehaviourComponent is destroyed.
	*/
	void Teardown() noexcept;
};

#endif
