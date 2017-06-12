#ifndef BLADE_PLAYER_CANNON_WEAPON_COMPONENT_H_
#define BLADE_PLAYER_CANNON_WEAPON_COMPONENT_H_
#include "weapon_component.h"
#include "timer.h"
/*
\brief Cannon weapon class specifies how a cannon shoot.
*/
class CannonWeaponComponent : public WeaponComponent
{
public:
	explicit CannonWeaponComponent(Blade::Entity* parent);

	CannonWeaponComponent(Blade::Entity* parent, WeaponPosition pos);

	virtual ~CannonWeaponComponent();

	void Shoot() override;

private:
	Blade::Timer m_Timer;
};



#endif