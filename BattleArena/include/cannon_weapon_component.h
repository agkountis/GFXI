#ifndef PLAYER_CANNON_WEAPON_COMPONENT_H_
#define PLAYER_CANNON_WEAPON_COMPONENT_H_
#include "weapon_component.h"
#include "timer.h"

/*
\brief Cannon weapon class specifies how a cannon shoot.
*/
class CannonWeaponComponent : public WeaponComponent
{
private:
	Blade::Timer m_Timer;

public:
	explicit CannonWeaponComponent(Blade::Entity* parent);

	CannonWeaponComponent(Blade::Entity* parent, WeaponPosition pos);

	virtual ~CannonWeaponComponent();

	void Shoot(const Blade::Vec3f& position) override;
};



#endif