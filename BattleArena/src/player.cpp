#include "player.h"
#include "engine_context.h"
#include <iostream>
#include "weapon_component.h"

using namespace Blade;

Player::Player(const std::string& name):
	Blade::Entity(name)
{

}


Player::~Player()
{


}
//LeftWeaponSocket
//RightWeaponSocket
bool Player::AddWeapon(Weapon * weapon)
{
	std::cout << "Add weapon" << std::endl;
	//left 
	if (m_WeaponCount ==0 )
	{
		weapon->SetPosition(GetEntityFromHierarchy("LeftWeaponSocket")->GetPosition());
		weapon->OnPickUp();
		G_SceneManager.GetCurrentScene()->RemoveEntity(weapon->GetName());
		this->AddChild(weapon);
		auto weaponComp{ static_cast<WeaponComponent*>(weapon->GetComponent("co_weapon")) };
		weaponComp->SetWeaponPosition(WeaponPosition::LEFT);

		weapon->RemoveComponent(weaponComp->GetId());

		this->AddComponent(weaponComp);
		weaponComp->SetParent(this);
		m_WeaponCount++;
		return true;
	}
	else if (m_WeaponCount == 1) //right
	{
		weapon->SetPosition(GetEntityFromHierarchy("RightWeaponSocket")->GetPosition());
		weapon->OnPickUp();
		G_SceneManager.GetCurrentScene()->RemoveEntity(weapon->GetName());
		this->AddChild(weapon);
		auto weaponComp{ static_cast<WeaponComponent*>(weapon->GetComponent("co_weapon")) };
		weaponComp->SetWeaponPosition(WeaponPosition::RIGHT);

		weapon->RemoveComponent(weaponComp->GetId());
		this->AddComponent(weaponComp);
		weaponComp->SetParent(this);
		m_WeaponCount++;
		return true;
	}
	return false;
}
