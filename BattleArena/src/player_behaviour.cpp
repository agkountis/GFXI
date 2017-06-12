#include "..\include\player_behaviour.h"



void PlayerBehaviour::LocalUpdate(const float dt, const long time) noexcept
{
}

void PlayerBehaviour::NetworkedUpdate(const float dt, const long time) noexcept
{
}

PlayerBehaviour::PlayerBehaviour(Entity* parent, bool local):
	Blade::BehaviourComponent("co_player_behaviour", parent),
	m_Local{ local }
{
}


PlayerBehaviour::~PlayerBehaviour()
{
}

void PlayerBehaviour::Update(const float dt, const long time) noexcept
{

	if (m_Local)
	{
		this->LocalUpdate(dt, time);
	}
	else
	{
		this->NetworkedUpdate(dt, time);
	}
}

void PlayerBehaviour::Setup() noexcept
{
}

void PlayerBehaviour::Teardown() noexcept
{
}

void PlayerBehaviour::OnCollision(Blade::Entity * other) noexcept
{
    BLADE_TRACE("Player collided with: " + other->GetName());

}
