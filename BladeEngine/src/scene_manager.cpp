#include "scene_manager.h"

namespace Blade
{
	void SceneManager::PushScene(std::unique_ptr<Scene> scene) noexcept
	{
		scene->Initialize();
		m_Scenes.push_back(std::move(scene));
	}

	void SceneManager::PopScene() noexcept
	{
		m_Scenes.pop_back();
	}

	void SceneManager::OnKeyDown(unsigned char key, int x, int y) noexcept
	{
		if (m_Scenes.back())
		{
			m_Scenes.back()->OnKeyDown(key, x, y);
		}
	}

	void SceneManager::OnKeyUp(unsigned char key, int x, int y) noexcept
	{
		if (m_Scenes.back())
		{
			m_Scenes.back()->OnKeyUp(key, x, y);
		}
	}

	void SceneManager::OnMouseMotion(int x, int y) noexcept
	{
		if (m_Scenes.back())
		{
			m_Scenes.back()->OnMouseMotion(x, y);
		}
	}

	void SceneManager::OnMouseClick(int button, bool state, int x, int y) noexcept
	{
		if (m_Scenes.back())
		{
			m_Scenes.back()->OnMouseClick(button, state, x, y);
		}
	}

	void SceneManager::OnMessage(const MessageContainer<std::string>& msg) noexcept
	{
		if (m_Scenes.back())
		{
			m_Scenes.back()->OnMessage(msg);
		}
	}

	void SceneManager::Update(float delta_time, long time) noexcept
	{
		if (m_Scenes.back())
		{
			m_Scenes.back()->Update(delta_time, time);
		}
	}

	void SceneManager::Draw() noexcept
	{
		if (m_Scenes.back())
		{
			m_Scenes.back()->Draw();
		}
	}
}
