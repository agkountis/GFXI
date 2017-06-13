#include "component.h"
#include "entity.h"
#include "engine_context.h"

namespace Blade
{
	int Component::s_IdCounter{ 0 };

	Component::Component(const std::string& type, Entity* parent) :
		m_Type{ type },
		p_Parent{ parent },
		m_Id{ ++s_IdCounter }
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

	void Component::SetParent(Entity * parent) noexcept
	{
		p_Parent = parent;
	}

	int Component::GetId() const noexcept
	{
		return m_Id;
	}

	void Component::OnMessage(const MessageContainer<std::string>& msg)
	{
		G_SceneManager.OnMessage(msg);
	}
}
