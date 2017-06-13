#ifndef PLAYER_CANNON_WEAPON_COMPONENT_H_
#define PLAYER_CANNON_WEAPON_COMPONENT_H_
#include "weapon_component.h"

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
};



#endif