#ifndef TEST_BEHAVIOUR
#define TEST_BEHAVIOUR

#include "behaviour_component.h"
#include "trace.h"
#include "entity.h"
#include <string>

class TestBehaviour : public Blade::BehaviourComponent
{
public:
	TestBehaviour(Blade::Entity* parent);
	virtual ~TestBehaviour();




	void Update(const float dt, const long time = 0) noexcept;

	/**
	* \brief Performs setup actions after the BehaviourComponent's creation
	*/
	void Setup() noexcept;;

	/**
	* \brief Performs actions before the BehaviourComponent is destroyed.
	*/
	void Teardown() noexcept;

	void OnCollision(Blade::Entity* other)noexcept

	{ 
		
		BLADE_TRACE("COLLISON INFO RELAYED TO BEHOAVIOUR COMPONENT, collision with: " + other->GetName());
	
	}
};

#endif