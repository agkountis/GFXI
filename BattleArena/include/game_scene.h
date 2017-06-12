#ifndef BATTLE_ARENA_GAME_SCENE_H_
#define BATTLE_ARENA_GAME_SCENE_H_
#include "scene.h"
#include "player_factory.h"
class GameScene : public Blade::Scene
{
public:
	void Initialize() override;

	void OnKeyDown(unsigned char key, int x, int y) noexcept override;

	void OnKeyUp(unsigned char key, int x, int y) noexcept override;

	void OnMouseMotion(int x, int y) noexcept override;

	void OnMouseClick(int button, bool state, int x, int y) noexcept override;

	void Update(float deltaTime, long time) noexcept override;

	void Draw() const noexcept override;
private:
	PlayerFactory m_PlayerFactory;
};

#endif //BATTLE_ARENA_GAME_SCENE_H_
