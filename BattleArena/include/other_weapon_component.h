#ifndef BLADE_PLAYER_OTHER_WEAPON_COMPONENT_H_
#define BLADE_PLAYER_OTHER_WEAPON_COMPONENT_H_
#include "weapon_component.h"

/*
\brief Placeholder weapon component
*/
class OtherWeaponComponent : public WeaponComponent
{
public:
	OtherWeaponComponent(Blade::Entity* parent, WeaponPosition pos);

	virtual ~OtherWeaponComponent();

	void Shoot() override;
};



#endif