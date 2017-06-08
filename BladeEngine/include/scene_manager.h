#ifndef BLADE_SCENE_MANAGER_H_
#define BLADE_SCENE_MANAGER_H_
#include <vector>
#include "scene.h"
#include <memory>

namespace Blade
{
	/*
	\brief Scene manager of the engine.
	\details Stores the collection of scenes and implement a FSM paradigm.
	*/
	class SceneManager
	{
	private:
		/*
		\brief The vector of the scenes.
		*/
		std::vector<std::unique_ptr<Scene>> m_Scenes;

	public:
		/*
		\brief Push a new scene in the manager.
		\details The scene in the back is the active one.
		*/
		void PushScene(std::unique_ptr<Scene> scene) noexcept;

		/*
		\brief Pop a scene to the manager.
		*/
		void PopScene() noexcept;

		/*
		\brief Propagate KeyDown information to the active scene.
		*/
		void OnKeyDown(unsigned char key, int x, int y) noexcept;

		/*
		\brief Propagate KeyUp information to the active scene.
		*/
		void OnKeyUp(unsigned char key, int x, int y) noexcept;

		/*
		\brief Propagate the mouse position to the active scene
		*/
		void OnMouseMotion(int x, int y) noexcept;

		/*
		\brief Propagate mouse click to the active scene
		*/
		void OnMouseClick(int button, bool state, int x, int y) noexcept;

		/*
		\brief Propagate the message from the application to the scene.
		*/
		void OnMessage(const MessageContainer<std::string>& msg) noexcept;

		/*
		\brief Calls update on the current scene.
		*/
		void Update(float delta_time, long time) noexcept;

		/*
		\brief Draw the current scene.
		*/
		void Draw() noexcept;
	};
}

#endif //BLADE_SCENE_MANAGER_H_
