#ifndef BLADE_PLAYER_BEHAVIOUR
#define BLADE_PLAYER_BEHAVIOUR
#include "behaviour_component.h"
#include "entity.h"


class PlayerBehaviour:public Blade::BehaviourComponent
{
private:
	bool m_Local{ false };

	void LocalUpdate(const float dt, const long time = 0) noexcept;

	void NetworkedUpdate(const float dt, const long time = 0) noexcept;

public:
	PlayerBehaviour(Blade::Entity* parent, bool local);
	~PlayerBehaviour();

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
	* \brief Method called when the collision with parent entity occurs
	* \param other entity that have collided with parent
	*/
	void OnCollision(Blade::Entity* other) noexcept override;
};

#endif