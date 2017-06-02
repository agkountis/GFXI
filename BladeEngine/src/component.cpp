#include "component.h"
#include "scene_manager.h"
#include "entity.h"

namespace Blade
{
	int Component::s_IdCounter{ 0 };

	Component::Component(const std::string& type, Entity* parent) :
		m_Type{ type }, 
		p_Parent{ parent },
		m_Id{++s_IdCounter }
	{
		parent->AddComponent(this);
	}

	Component::~Component()
	{
	}

	const std::string& Component::GetType() const noexcept
	{
		return m_Type;
	}

	Entity* Component::GetParent() const noexcept
	{
		return p_Parent;
	}

	int Component::GetId() const noexcept
	{
		return m_Id;
	}

	void Component::OnMessage(const MessageContainer& msg)
	{
		SceneManager::OnMessage(msg);
	}
}
