#ifndef BATTLE_ARENA_BULLET_H_
#define BATTLE_ARENA_BULLET_H_

#include "entity.h"
#include "material.h"


class Bullet : public Blade::Entity
{
public:
	Bullet(const std::string & name, const std::wstring & mesh, const Blade::Material & material, const float radius, 
		const float mass, const Blade::Vec3f & position, const Blade::Vec3f & velocity);
};

#endif