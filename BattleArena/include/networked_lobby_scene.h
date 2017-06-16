#ifndef NETWORKED_LOBBY_SCENE_H_
#define NETWORKED_LOBBY_SCENE_H_
#include "scene.h"
#include "player.h"

class NetworkedLobbyScene : public Blade::Scene
{
private:
	std::vector<PlayerInfo> m_PlayerInfos;

public:
	bool Initialize() override;
	void OnKeyDown(unsigned char key, int x, int y) noexcept override;
	void OnKeyUp(unsigned char key, int x, int y) noexcept override;
	void OnMouseMotion(int x, int y) noexcept override;
	void OnMouseClick(int button, bool state, int x, int y) noexcept override;
	void Draw() const noexcept override;
	void Update(float deltaTime, long time) noexcept override;
};

#endif