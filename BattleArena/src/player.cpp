#include "player.h"
#include "engine_context.h"
#include <iostream>
#include "weapon_component.h"

using namespace Blade;

Player::Player(const std::string& name)
	: Entity(name)
{
}

bool Player::AddWeapon(Weapon* weapon) noexcept
{
	if (m_WeaponCount < 2)
	{
		BLADE_TRACE("Add weapon");
		++m_WeaponCount;
		(m_WeaponCount == 1) ? weapon->SetPosition(m_LeftWeaponPos) : weapon->SetPosition(m_RightWeaponPos);

		weapon->OnPickUp();
		G_SceneManager.GetCurrentScene()->RemoveEntity(weapon->GetName());
		//GetEntityFromHierarchy("LeftWeaponSocket")->AddChild(weapon);
		AddChild(weapon);

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
	//entity->SetOrientation(glm::rotate(q, rotationVec.x*dt, glm::vec3(0, 1, 0)));

	//use orientation to influence the force that is being added to the simulation component
	Vec3f output = Vec3f(Mat4f(q) * Vec4f(0, 0, 1, 0));

	return output;
}

void Player::SetWeaponPositions(const Vec3f & leftWeaponPos, const Vec3f & rightWeaponPos) noexcept
{
	m_LeftWeaponPos = leftWeaponPos;

	m_RightWeaponPos = rightWeaponPos;
}

const Vec3f & Player::GetLeftWeaponPos()  noexcept
{
	
	return (GetXform() * Vec4f(m_LeftWeaponPos,1.0f)).xyz;
}

const Blade::Vec3f & Player::GetRightWeaponPos()  noexcept
{
	return (GetXform() * Vec4f(m_RightWeaponPos, 1.0f)).xyz;
}