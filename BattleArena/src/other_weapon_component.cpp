#include "other_weapon_component.h"
#include <iostream>

using namespace Blade;

OtherWeaponComponent::OtherWeaponComponent(Blade::Entity * parent):
	WeaponComponent(parent)
{
}

OtherWeaponComponent::OtherWeaponComponent(Blade::Entity* parent, WeaponPosition pos):
	WeaponComponent( pos, parent)
{
}


OtherWeaponComponent::~OtherWeaponComponent()
{

}

void OtherWeaponComponent::Shoot()
{
	std::cout << "Green weapon!" << std::endl;
}
