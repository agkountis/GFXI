#include "player_behaviour.h"
#include "weapon.h"
#include "player.h"
#include "bullet.h"

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
	if (dynamic_cast<Weapon*>(other))
	{
		Player* me = static_cast<Player*>(GetParent());
		Weapon* wpn = static_cast<Weapon*>(other);
		me->AddWeapon(wpn);
	}
}
