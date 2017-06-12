#ifndef BATTLE_ARENA_WEAPON_H_
#define BATTLE_ARENA_WEAPON_H_

#include "entity.h"

class Weapon :public  Blade::Entity
{
public:
	Weapon(const std::string name);
	~Weapon();
	void OnPickUp();

};
#endif
