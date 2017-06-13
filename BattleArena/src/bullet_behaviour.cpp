#include "bullet_behaviour.h"
#include <iostream>
using namespace Blade;

BulletBehaviour::BulletBehaviour(Blade::Entity* parent):
	BehaviourComponent("co_bullet_behaviour",parent)
{

}

void BulletBehaviour::Update(const float dt, const long time /*= 0*/) noexcept
{

}

void BulletBehaviour::Setup() noexcept
{

}

void BulletBehaviour::Teardown() noexcept
{

}

void BulletBehaviour::OnCollision(Blade::Entity* other) noexcept
{
	GetParent()->SetAlive(false);
}
