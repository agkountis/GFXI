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

	WeaponComponent(Blade::Entity* parent);

	virtual ~WeaponComponent();

	virtual void Shoot() = 0;

	WeaponPosition GetWeaponPosition() const { return m_WeaponPos; };

	void SetWeaponPosition(const WeaponPosition position) { m_WeaponPos = position; };

private:

	WeaponPosition m_WeaponPos;
};



#endif