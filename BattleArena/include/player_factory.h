#include "player.h"

class PlayerFactory
{
public:
	Player* CreateLocalKeyboardPlayer(const std::string& name, const std::wstring& modelPath);

	Player* CreateLocalJoypadPlayer(const std::string& name, const std::wstring& modelPath);

	Player* CreateMultiplayerPlayer(const std::string& name, const std::wstring& modelPath);


private:
	unsigned int m_Counter{ 0 };
	bool m_KeyboardPlayer{ false };


};