#ifndef PLAYER_H_
#define PLAYER_H_
#include "entity.h"
#include "weapon.h"

struct PlayerInfo
{
	std::string playerName;
	std::wstring fileName;
	Blade::Vec3f spawnLocation;

	PlayerInfo(const std::string& pName, const std::wstring& fName, const Blade::Vec3f& spLocation)
		: playerName{pName},
		  fileName{fName},
		  spawnLocation{spLocation}
	{
	}
};

class Player : public Blade::Entity
{
private:
	int m_WeaponCount{0};
	int m_Id;
	Blade::Vec3f m_LeftWeaponPos;
	Blade::Vec3f m_RightWeaponPos;
public:
	explicit Player(const std::string& name,const int id);

	bool AddWeapon(Weapon* weapon) noexcept;

	Blade::Vec3f GetHeading() const noexcept;

	Blade::Vec3f GetLeftWeaponPos() noexcept;

	Blade::Vec3f GetRightWeaponPos() noexcept;

	int GetID() const noexcept;

	void Explode(const Blade::Vec3f& position);


	void SetWeaponPositions(const Blade::Vec3f& leftWeaponPos, const Blade::Vec3f rightWeaponPos);


};

#endif
