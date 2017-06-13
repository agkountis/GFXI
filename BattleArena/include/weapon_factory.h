#ifndef BLADE_ARENA_WEAPON_FACTORY_H_
#define BLADE_ARENA_WEAPON_FACTORY_H_
#include "weapon.h"
#include "emitter_component.h"

class WeaponFactory
{
private:
	int m_counter{ 0 }; //Maybe we can use this to set up different weapons position inside the creation.

	/*
	#todo implement weapon spawning position logic
	*/
	Blade::EmitterDescriptor m_DescriptorWeapon1;

	Blade::EmitterDescriptor m_DescriptorWeapon2;

public:
	WeaponFactory();

	Weapon* CreateWeapon1(const std::string& name);

	Weapon* CreateWeapon2(const std::string& name) const;
};

#endif //WEAPON_FACTORY_H_
