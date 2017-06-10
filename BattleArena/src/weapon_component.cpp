#include "weapon_component.h"

using namespace Blade;

WeaponComponent::WeaponComponent(WeaponPosition pos, Blade::Entity * parent):
	Component("co_weapon", parent),m_WeaponPos(pos)
{
}

WeaponComponent::~WeaponComponent()
{

}
