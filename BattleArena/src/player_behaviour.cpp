#include "player_behaviour.h"
#include "weapon.h"
#include "player.h"

using namespace Blade;

void PlayerBehaviour::LocalUpdate(const float dt, const long time) noexcept
{
}

void PlayerBehaviour::NetworkedUpdate(const float dt, const long time) noexcept
{
}

PlayerBehaviour::PlayerBehaviour(Entity* parent, bool local)
	: BehaviourComponent("co_player_behaviour", parent),
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

void PlayerBehaviour::OnCollision(Entity* other) noexcept
{
	BLADE_TRACE("Player collided with: " + other->GetName());
	if (dynamic_cast<Weapon*>(other))
	{
		BLADE_TRACE("COLLIDE WITH WEAPON" + other->GetName());
		//Update parent and child
		//GetParent()->AddChild(other);
		Player* me = static_cast<Player*>(GetParent());

		Weapon* wpn = static_cast<Weapon*>(other);
		me->AddWeapon(wpn);
	}
}
