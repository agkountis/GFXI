#include "explosion_behaviour.h"
#include "Entity.h"

using namespace Blade;

ExplosionBehaviour::ExplosionBehaviour(Entity* entity, float lifetimeInSceconds):
	BehaviourComponent("co_behaviour",entity),
	m_Lifetime(lifetimeInSceconds)
{
	m_Timer.Start();
}


ExplosionBehaviour::~ExplosionBehaviour()
{
}

void ExplosionBehaviour::Update(const float dt, const long time) noexcept
{
	if (m_Timer.GetSec() > m_Lifetime)
	{
		GetParent()->SetAlive(false);
	}
}

void ExplosionBehaviour::Setup() noexcept
{
}

void ExplosionBehaviour::Teardown() noexcept
{
}

