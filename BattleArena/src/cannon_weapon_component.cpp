#include "cannon_weapon_component.h"
#include <iostream>
#include "engine_context.h"
#include "entity.h"
#include "bullet.h"
#include "simulation_component.h"
#include "player.h"
using namespace Blade;

CannonWeaponComponent::CannonWeaponComponent(Blade::Entity* parent):
	WeaponComponent(parent)
{
	m_Timer.Start();
}

CannonWeaponComponent::CannonWeaponComponent(Blade::Entity* parent, WeaponPosition pos):
	WeaponComponent(pos, parent)
{
}

CannonWeaponComponent::~CannonWeaponComponent()
{
}

void CannonWeaponComponent::Shoot(const Vec3f& position)
{
	if (m_Timer.GetMsec() > 1000)
	{
		std::cout << "Red weapon!!" << std::endl;
		Material material;
		material.diffuse = Vec4f{ 40.0f, 1.0f, 1.0f, 1.0f };
		material.specular = Vec4f{ 1.0f, 1.0f, 1.0f, 60.0f }; //the w value is the shininess.

		auto p{ static_cast<Player*>(GetParent()) };

		Bullet* cannonBullet{ new Bullet("cannon_bullet", L"cube", material, 0.3f, 0.5f,
			position-Vec3f(0.0f,0.25f,0.0f),
			p->GetHeading()*100.0f) };

		G_SceneManager.GetCurrentScene()->AddEntity(cannonBullet);
		m_Timer.Reset();
	}
}
