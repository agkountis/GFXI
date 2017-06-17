#ifndef NETWORKED_GAME_SCENE_H_
#define NETWORKED_GAME_SCENE_H_
#include "scene.h"
#include "player.h"
#include "weapon_factory.h"
#include "player_factory.h"

#ifdef BLADE_BUILD_OVR
class GameSceneColorPassStageOvr;
#endif

class NetworkedGameScene : public Blade::Scene
{
private:
	PlayerFactory m_PlayerFactory;
	std::vector<PlayerInfo> m_PlayerInfos;
	std::vector<Player*> m_Players;
	WeaponFactory m_WeaponFactory;


#ifdef BLADE_BUILD_OVR
	GameSceneColorPassStageOvr* ovrStage{ nullptr };
#endif

public:
	NetworkedGameScene(const std::vector<PlayerInfo>& pInfos);

	bool Initialize() override;
	void OnKeyDown(unsigned char key, int x, int y) noexcept override;
	void OnKeyUp(unsigned char key, int x, int y) noexcept override;
	void OnMouseMotion(int x, int y) noexcept override;
	void OnMouseClick(int button, bool state, int x, int y) noexcept override;
	void Update(float deltaTime, long time) noexcept override;
	void Draw() const noexcept override;
};

#endif //NETWORKED_GAME_SCENE_H_
