#pragma once
#ifndef BATTLE_ARENA_PLAYER_H_
#define BATTLE_ARENA_PLAYER_H_
#include "entity.h"
#include "health_component.h"

using namespace Blade;

class Player : public Blade::Entity
{
public:
	Player(const std::string& name);
	~Player();
};

#endif