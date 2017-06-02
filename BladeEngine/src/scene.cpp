#include "scene.h"
#include "entity.h"

namespace Blade
{
	Scene::~Scene()
	{
		for (const auto object : m_Entities)
		{
			delete object;
		}

		m_Entities.clear();
	}

	void Scene::AddEntity(Entity* object) noexcept
	{
		m_Entities.push_back(object);
	}

	void Scene::Update(float delta_time, long time) noexcept
	{
		auto it{ m_Entities.begin() };

		while (it != m_Entities.end())
		{
			auto object{ *it };
			if (!object->IsAlive())
			{
				delete object;
				it = m_Entities.erase(it);
			}
			else
			{
				object->Update(delta_time, time);
				++it;
			}
		}
	}

	void Scene::OnMessage(const MessageContainer<std::string>& msg) const noexcept
	{
		for (auto object : m_Entities)
		{
			object->BroadcastMessage(msg);
		}
	}
}
