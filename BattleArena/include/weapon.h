#ifndef WEAPON_H_
#define WEAPON_H_

#include "entity.h"

class Weapon :public  Blade::Entity
{
public:
	Weapon(const std::string name);
	~Weapon();
	void OnPickUp();

};
#endif
