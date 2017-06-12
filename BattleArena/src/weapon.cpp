#include "weapon.h"
#include "collider_component.h"
using namespace Blade;

Weapon::Weapon(const std::string name):
	Entity(name)
{
}

Weapon::~Weapon()
{
}

void Weapon::OnPickUp()
{
	//Disable the collider component
	auto collider{ static_cast<ColliderComponent*>(this->GetComponent("co_col")) };
	collider->SetCollisionResponseFlag(false);
}
