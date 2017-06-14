#ifndef BLADE_ARENA_WEAPON_FACTORY_H_
#define BLADE_ARENA_WEAPON_FACTORY_H_
#include "weapon.h"
#include "emitter_component.h"

class WeaponFactory
{
private:
	int m_counter{ 0 }; //Maybe we can use this to set up different weapons position inside the creation.


	Blade::EmitterDescriptor m_DescriptorWeapon1;

	Blade::EmitterDescriptor m_DescriptorWeapon2;

	Blade::Entity * m_Arena;


	Weapon* CreateWeapon1(const std::string& name, const Blade::Vec3f& pos) const noexcept;

	Weapon* CreateWeapon2(const std::string& name, const Blade::Vec3f& pos) const noexcept;

public:
	void SetArena(Blade::Entity* arena) noexcept;

	WeaponFactory();


	void GenerateWeapons() const noexcept;
};

#endif //WEAPON_FACTORY_H_
