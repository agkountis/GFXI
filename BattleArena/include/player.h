#pragma once
#ifndef BATTLE_ARENA_PLAYER_H_
#define BATTLE_ARENA_PLAYER_H_
#include "entity.h"
#include "health_component.h"



class Player : public Blade::Entity
{

public:
	Player(const std::string& name);
	~Player();

	/*
	\brief Get Players foreward vector
	\return player's  forward vector
	*/
	Blade::Vec3f GetHeading() noexcept;
};

#endif