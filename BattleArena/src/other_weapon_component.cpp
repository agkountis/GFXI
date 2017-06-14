#include "other_weapon_component.h"
#include "engine_context.h"
#include "projectile.h"
#include "player.h"
using namespace Blade;

OtherWeaponComponent::OtherWeaponComponent(Blade::Entity * parent):
	WeaponComponent(parent)
{
	m_Timer.Start();
}

OtherWeaponComponent::OtherWeaponComponent(Blade::Entity* parent, WeaponPosition pos):
	WeaponComponent( pos, parent)
{
}


OtherWeaponComponent::~OtherWeaponComponent()
{

}

void OtherWeaponComponent::Shoot(const Vec3f & position)
{
	if (m_Timer.GetMsec() > 500)
	{
		auto p{ static_cast<Player*>(GetParent()) };
		std::cout << "Green weapon!!" << std::endl;
		Material material;
		material.diffuse = Vec4f{ 1.0f, 55.0f, 1.0f, 1.0f };
		material.specular = Vec4f{ 1.0f, 1.0f, 1.0f, 60.0f }; //the w value is the shininess.

		//Mat4f rot{};
		//rot = MathUtils::Rotate(rot, 30.0f, Vec3f(1.0f, 0.0f, 0.0f));
		auto heading{ p->GetHeading() +Vec3f(0.0f,1.275,0.0f)};
		//auto velocity{  Vec3f(rot * Vec4f(heading,1.0f)) *20.0f};

		
		Projectile* otherWeaponBullet{ new Projectile("projectile_2", L"cube", material, 1.5f, 0.5f,
			position,
			heading*9.945f)};

		G_SceneManager.GetCurrentScene()->AddEntity(otherWeaponBullet);
		m_Timer.Reset();
	}
}
