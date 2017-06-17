#ifndef MAIN_SCENE_H_
#define MAIN_SCENE_H_
#include "scene.h"

class MainScene : public Blade::Scene
{
private:
	Blade::Entity* m_pBillobard;
	Blade::Entity* m_pScreen;
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
