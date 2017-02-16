#include "component.h"
#include "scene_manager.h"
#include "entity.h"

namespace Blade
{
	Component::~Component()
	{
	}

	Component::Component(const std::string& type, Entity* parent) : m_Type{ type }, p_Parent{ parent }
	{
		parent->AddComponent(this);
	}

	void Component::OnMessage(const MessageContainer& msg)
	{
		SceneManager::OnMessage(msg);
	}
}
