#include "scene_manager.h"

namespace Blade
{
	std::vector<Scene*> SceneManager::m_Scenes;

	SceneManager::~SceneManager()
	{
		for (auto scene : m_Scenes)
		{
			delete scene;
		}

		m_Scenes.clear();
	}

	void SceneManager::PushScene(Scene* scene) noexcept
	{
		scene->Initialize();
		m_Scenes.push_back(scene);
	}

	Scene* SceneManager::PopScene() noexcept
	{
		Scene* sc{ m_Scenes.back() };

		m_Scenes.erase(m_Scenes.end());

		return sc;
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

	void SceneManager::OnMessage(const MessageContainer& msg) noexcept
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
