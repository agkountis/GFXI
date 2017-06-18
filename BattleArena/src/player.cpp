#include "player.h"
#include "engine_context.h"
#include <iostream>
#include "weapon_component.h"
#include "explosion.h"
using namespace Blade;

Player::Player(const std::string& name,const int id)
	: Entity(name),m_Id{id}
{
}

bool Player::AddWeapon(Weapon* weapon) noexcept
{
	if (m_WeaponCount < 2)
	{
		BLADE_TRACE("Add weapon");
		++m_WeaponCount;
		weapon->SetPosition(Vec3f(.0f,.0f,.0f));
		if (m_WeaponCount == 1)
		{
			GetEntityFromHierarchy("LeftWeaponSocket")->AddChild(weapon);
		}
		else
		{
			GetEntityFromHierarchy("RightWeaponSocket")->AddChild(weapon);
		}

		weapon->OnPickUp();
		G_SceneManager.GetCurrentScene()->RemoveEntity(weapon->GetName());
		//GetEntityFromHierarchy("LeftWeaponSocket")->AddChild(weapon);
		//AddChild(weapon);

		auto weaponComp{ static_cast<WeaponComponent*>(weapon->GetComponent("co_weapon")) };
		weaponComp->SetWeaponPosition(static_cast<WeaponPosition>(m_WeaponCount-1));
		weapon->RemoveComponent(weaponComp->GetId());
		AddComponent(weaponComp);
		weaponComp->SetParent(this);

		return true;
	}
	return false;
}

Vec3f Player::GetHeading() const noexcept
{
	//change orientation
	Quatf q = this->GetOrientation();
	Vec3f output = Vec3f(Mat4f(q) * Vec4f(0, 0, 1, 0));

	return output;
}

Vec3f Player::GetLeftWeaponPos() noexcept
{
	Update(0, 0);
	return GetEntityFromHierarchy("LeftWeaponSocket")->GetWorldPosition();
}

Vec3f Player::GetRightWeaponPos() noexcept
{
	Update(0, 0);
	return GetEntityFromHierarchy("RightWeaponSocket")->GetWorldPosition();
}

int Player::GetID() const noexcept
{
	return m_Id;
}

void Player::Explode(const Vec3f& position)
{
	Explosion* expl = new Explosion(0.9f);
	expl->SetPosition(position);
	expl->RegisterWithScene();
}
