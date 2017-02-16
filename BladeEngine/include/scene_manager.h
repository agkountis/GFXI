#ifndef BLADE_SCENE_MANAGER_H_
#define BLADE_SCENE_MANAGER_H_
#include <vector>
#include "scene.h"

namespace Blade
{
	class SceneManager
	{
	private:
		static std::vector<Scene*> m_Scenes;

	public:
		SceneManager() = default;

		~SceneManager();

		SceneManager(const SceneManager&) = delete;

		SceneManager& operator=(const SceneManager&) = delete;

		static void PushScene(Scene* scene) noexcept;

		static Scene* PopScene() noexcept;

		static void OnKeyDown(unsigned char key, int x, int y) noexcept;

		static void OnKeyUp(unsigned char key, int x, int y) noexcept;

		static void OnMouseMotion(int x, int y) noexcept;

		static void OnMouseClick(int button, bool state, int x, int y) noexcept;

		// Respond to messages
		static void OnMessage(const MessageContainer& msg) noexcept;

		static void Update(float delta_time, long time) noexcept;

		static void Draw() noexcept;
	};
}

#endif //BLADE_SCENE_MANAGER_H_
