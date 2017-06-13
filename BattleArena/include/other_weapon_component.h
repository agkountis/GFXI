#ifndef OTHER_WEAPON_COMPONENT_H_
#define OTHER_WEAPON_COMPONENT_H_
#include "weapon_component.h"

/*
\brief Placeholder weapon component
*/
class OtherWeaponComponent : public WeaponComponent
{
public:
	explicit OtherWeaponComponent(Blade::Entity* parent);

	OtherWeaponComponent(Blade::Entity* parent, WeaponPosition pos);

	virtual ~OtherWeaponComponent();

	void Shoot() override;
};



#endif