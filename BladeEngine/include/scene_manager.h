#ifndef BLADE_SCENE_MANAGER_H_
#define BLADE_SCENE_MANAGER_H_
#include <vector>
#include "scene.h"
#include <memory>
#include "singleton.h"

namespace Blade
{
	class SceneManager : public Singleton<SceneManager>
	{
	private:
		std::vector<std::unique_ptr<Scene>> m_Scenes;

	public:
		void PushScene(std::unique_ptr<Scene> scene) noexcept;

		void PopScene() noexcept;

		void OnKeyDown(unsigned char key, int x, int y) noexcept;

		void OnKeyUp(unsigned char key, int x, int y) noexcept;

		void OnMouseMotion(int x, int y) noexcept;

		void OnMouseClick(int button, bool state, int x, int y) noexcept;

		void OnMessage(const MessageContainer<std::string>& msg) noexcept;

		void Update(float delta_time, long time) noexcept;

		void Draw() noexcept;
	};

#define STN_SceneManager SceneManager::GetInstance()
}

#endif //BLADE_SCENE_MANAGER_H_
