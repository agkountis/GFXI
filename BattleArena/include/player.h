#pragma once
#ifndef BATTLE_ARENA_PLAYER_H_
#define BATTLE_ARENA_PLAYER_H_


#include "entity.h"
#include "render_component.h"
#include "mesh_utils.h"
#include "resource_manager.h"
#include "simulation_component.h"
#include "collider_component.h"
#include "bounding_sphere.h"
#include "emitter_component.h"
#include "player_joypad_component.h"
#include "test_behaviour.h"
#include "cannon_weapon_component.h"
#include "other_weapon_component.h"
#include "d3d/D3D11_texture.h"

#include "player_behaviour.h"

using namespace Blade;

class Player : public Blade::Entity
{
private:
	static int m_InstanceCount;
public:
	Player(const std::string& name, const std::wstring& modelPath,bool local);
	~Player();


};

#endif