#ifndef NETWORKED_LOBBY_SCENE_H_
#define NETWORKED_LOBBY_SCENE_H_
#include "scene.h"
#include "player.h"
#include "timer.h"

#ifdef BLADE_BUILD_OVR
class GameSceneColorPassStageOvr;
#else
class GameSceneColorPassStage;
#endif


class NetworkedLobbyScene : public Blade::Scene
{
private:
	std::vector<PlayerInfo> m_PlayerInfos;
	Blade::Entity* m_pBillobard;
	Blade::Entity* m_pScreen;


	Blade::Timer m_Timer;
	bool m_Fading{ false };

#ifdef BLADE_BUILD_OVR
	GameSceneColorPassStageOvr* ovrStage{ nullptr };
#else
	GameSceneColorPassStage* m_ColorPass{ nullptr };
#endif

	void FadeOutLogic(float deltaTime);


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