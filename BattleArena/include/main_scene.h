#ifndef MAIN_SCENE_H_
#define MAIN_SCENE_H_
#include "scene.h"
#include "timer.h"
#ifdef BLADE_BUILD_OVR
class GameSceneColorPassStageOvr;
#else
class GameSceneColorPassStage;
#endif


enum class Move 
{
	LEFT,
	RIGHT 
};

enum class CurrentState
{
	LOGO,
	LOCAL,
	NETWORK
};

class MainScene : public Blade::Scene
{
private:

	Blade::Entity* m_pBillobard;
	Blade::Entity* m_pScreen;

	void CheckInputDevice();
	void OnMove(Move move);
	void OnPress();
	CurrentState m_State{ CurrentState::LOGO };

	Blade::Timer m_Timer;
	bool m_Fading{ false };

#ifdef BLADE_BUILD_OVR
	GameSceneColorPassStageOvr* ovrStage{ nullptr };
#else
	GameSceneColorPassStage* m_ColorPass{ nullptr };
#endif

	void FadeOutLogic(float deltaTime) const;


public:
	bool Initialize() override;

	void OnKeyDown(unsigned char key, int x, int y) noexcept override;

	void OnKeyUp(unsigned char key, int x, int y) noexcept override;

	void OnMouseMotion(int x, int y) noexcept override;

	void OnMouseClick(int button, bool state, int x, int y) noexcept override;

	void Update(float deltaTime, long time) noexcept override;

	void Draw() const noexcept override;
};

#endif //MAIN_SCENE_H_
