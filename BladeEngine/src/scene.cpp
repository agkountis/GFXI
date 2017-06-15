#include "scene.h"
#include "entity.h"

namespace Blade
{
	Scene::~Scene()
	{
		for (const auto object : m_pEntities)
		{
			delete object;
		}

		m_pEntities.clear();
	}

	void Scene::AddEntity(Entity* object) noexcept
	{
		m_pEntities.push_back(object);
	}


	void Scene::RemoveEntity(const std::string& name) noexcept
	{
		for (auto entity : m_pEntities)
		{
			if (entity->GetName() == name)
			{
				m_pNeedToBeRemovedEntities.push_back(entity);
			}
		}
	}

	void Scene::RemoveEntities() noexcept
	{

		for(auto needToBeRemovedEntity: m_pNeedToBeRemovedEntities)
		{
			auto it{ m_pEntities.begin() };

			while (it != m_pEntities.end())
			{
				auto entry{ *it };
				if (entry->GetName() == needToBeRemovedEntity->GetName())
				{
					it = m_pEntities.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
		m_pNeedToBeRemovedEntities.clear();
	}

	const std::vector<Entity*>& Scene::GetEntities() const noexcept
	{
		return m_pEntities;
	}

	Entity * Scene::GetEntityByName(const std::string & name) noexcept
	{
		for (auto entity : m_pEntities)
		{
			if (entity->GetName() == name)
			{
				return entity;
			}
		}
	}

	void Scene::Update(float delta_time, long time) noexcept
	{
		RemoveEntities();

		auto it{ m_pEntities.begin() };

		while (it != m_pEntities.end())
		{
			auto object{ *it };
			if (!object->IsAlive())
			{
				delete object;
				it = m_pEntities.erase(it);
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
		for (auto object : m_pEntities)
		{
			object->BroadcastMessage(msg);
		}
	}
}
