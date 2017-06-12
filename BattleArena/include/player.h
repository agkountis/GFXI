#ifndef BATTLE_ARENA_PLAYER_H_
#define BATTLE_ARENA_PLAYER_H_
#include "entity.h"
#include "weapon.h"
using namespace Blade;

class Player : public Blade::Entity
{
public:
	Player(const std::string& name);
	~Player();

	bool AddWeapon(Weapon* weapon);

private:
	int m_WeaponCount{ 0 };
};

#endif