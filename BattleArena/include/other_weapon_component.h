#ifndef OTHER_WEAPON_COMPONENT_H_
#define OTHER_WEAPON_COMPONENT_H_
#include "weapon_component.h"
#include "timer.h"
/*
\brief Placeholder weapon component
*/
class OtherWeaponComponent : public WeaponComponent
{
private:
	Blade::Timer m_Timer;

public:
	explicit OtherWeaponComponent(Blade::Entity* parent);

	OtherWeaponComponent(Blade::Entity* parent, WeaponPosition pos);

	virtual ~OtherWeaponComponent();

	void Shoot(const Blade::Vec3f& position) override;
	
};



#endif