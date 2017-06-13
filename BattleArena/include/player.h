#ifndef PLAYER_H_
#define PLAYER_H_
#include "entity.h"
#include "weapon.h"

class Player : public Blade::Entity
{
private:
	int m_WeaponCount{ 0 };

public:
	explicit Player(const std::string& name);

	bool AddWeapon(Weapon* weapon) noexcept;

	Blade::Vec3f GetHeading() const noexcept;
};

#endif
