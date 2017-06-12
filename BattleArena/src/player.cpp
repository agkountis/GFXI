#include "player.h"
#include "engine_context.h"
#include <iostream>
#include "weapon_component.h"

using namespace Blade;

Player::Player(const std::string& name)
	: Entity(name)
{
}

//LeftWeaponSocket
//RightWeaponSocket
bool Player::AddWeapon(Weapon* weapon) noexcept
{
	BLADE_TRACE("Add weapon");

	//left
	if (m_WeaponCount == 0)
	{
		weapon->SetPosition(GetEntityFromHierarchy("LeftWeaponSocket")->GetPosition());
		weapon->OnPickUp();

		G_SceneManager.GetCurrentScene()->RemoveEntity(weapon->GetName());
		AddChild(weapon);

		auto weaponComp{ static_cast<WeaponComponent*>(weapon->GetComponent("co_weapon")) };
		weaponComp->SetWeaponPosition(WeaponPosition::LEFT);

		weapon->RemoveComponent(weaponComp->GetId());

		AddComponent(weaponComp);
		weaponComp->SetParent(this);
		++m_WeaponCount;

		return true;
	}

	if (m_WeaponCount == 1) //right
	{
		weapon->SetPosition(GetEntityFromHierarchy("RightWeaponSocket")->GetPosition());
		weapon->OnPickUp();
		G_SceneManager.GetCurrentScene()->RemoveEntity(weapon->GetName());

		AddChild(weapon);

		auto weaponComp{ static_cast<WeaponComponent*>(weapon->GetComponent("co_weapon")) };
		weaponComp->SetWeaponPosition(WeaponPosition::RIGHT);

		weapon->RemoveComponent(weaponComp->GetId());
		this->AddComponent(weaponComp);
		weaponComp->SetParent(this);

		++m_WeaponCount;

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
