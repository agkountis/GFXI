#ifndef BLADE_PLAYER_WEAPON_COMPONENT_H_
#define BLADE_PLAYER_WEAPON_COMPONENT_H_
#include "component.h"

/*
\brief Weapon component is an abstract class that uniforms the 
weapons design. 
*/

enum class WeaponPosition { LEFT, RIGHT};


class WeaponComponent : public Blade::Component
{
public:
	WeaponComponent(WeaponPosition pos, Blade::Entity* parent);

	virtual ~WeaponComponent();

	virtual void Shoot() = 0;

	WeaponPosition m_WeaponPos;
};



#endif