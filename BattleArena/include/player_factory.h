#ifndef PLAYER_FACTORY_H_
#define PLAYER_FACTORY_H_

#include "player.h"
#include "health_bar_factory.h"


class PlayerFactory
{
private:
	unsigned int m_Counter{ 0 };
	bool m_KeyboardPlayer{ false };
	HealthBarFactory m_HealthBarFactory;

public:

	Player* PlayerFactory::CreateKeyboardPlayer(const std::string& name, const std::wstring& modelPath, const int playerID, bool online) noexcept;

	Player* PlayerFactory::CreateJoypadPlayer(const std::string& name, const std::wstring& modelPath, const int playerID, bool online) noexcept;

	Player* CreatePlayer(const std::string& name, const std::wstring& modelPath, const int playerID) noexcept;
};
#endif