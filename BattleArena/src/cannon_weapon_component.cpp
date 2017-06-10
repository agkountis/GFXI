#include "cannon_weapon_component.h"
#include <iostream>
#include "engine_context.h"
#include "entity.h"
#include "bullet.h"
#include "simulation_component.h"

using namespace Blade;



CannonWeaponComponent::CannonWeaponComponent(Blade::Entity * parent, WeaponPosition pos):
	WeaponComponent(pos, parent)
{
	m_Timer.Start();
}

CannonWeaponComponent::~CannonWeaponComponent()
{

}

void CannonWeaponComponent::Shoot()
{

	if(m_Timer.GetMsec() >1000)
	{
	using namespace Blade;
	std::cout << "Cannon!!" << std::endl;
	Material material;
	material.diffuse = Vec4f{ 40.0f, 1.0f, 1.0f, 1.0f };
	material.specular = Vec4f{ 1.0f, 1.0f, 1.0f, 60.0f }; //the w value is the shininess.

	auto simComp = static_cast<SimulationComponent*>(GetParent()->GetComponent("co_sim"));

	auto velocity = Blade::MathUtils::Normalize(simComp->GetVelocity()) * 50.0f;

	Bullet* cannonBullet{ new Bullet("cannon_bullet",L"cube",material,1.0f,0.5f,
		GetParent()->GetPosition() + Vec3f(2.5f,2.5f,2.5f),
		velocity )};
	
	G_SceneManager.GetCurrentScene()->AddEntity(cannonBullet);
	m_Timer.Reset();
	}

}
