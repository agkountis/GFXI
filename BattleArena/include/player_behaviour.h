#ifndef BLADE_PLAYER_BEHAVIOUR
#define BLADE_PLAYER_BEHAVIOUR

#include "behaviour_component.h"
#include "trace.h"
#include "entity.h"
#include <string>

using namespace Blade;
class PlayerBehaviour:public Blade::BehaviourComponent
{
private:
	bool m_Local{ false };

	void LocalUpdate(const float dt, const long time = 0) noexcept;
	void NetworkedUpdate(const float dt, const long time = 0) noexcept;

public:
	PlayerBehaviour(Entity* parent, bool local);
	~PlayerBehaviour();



	void Update(const float dt, const long time = 0) noexcept;

	/**
	* \brief Performs setup actions after the BehaviourComponent's creation
	*/
	void Setup() noexcept;;

	/**
	* \brief Performs actions before the BehaviourComponent is destroyed.
	*/
	void Teardown() noexcept;


	/**
	* \brief Method called when the collision with parent entity occurs
	* \param Other entity that have collided with parent
	*/
	void OnCollision(Blade::Entity* other)noexcept;
};

#endif