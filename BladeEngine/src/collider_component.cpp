#include "collider_component.h"
#include "entity.h"
#include "simulation_system.h"
#include "engine_context.h"
#include "behaviour_component.h"

using namespace Blade;

void Blade::ColliderComponent::NotifyCollisionListeners(Entity* entity) noexcept
{
	//BLADE_TRACE("COLLIDER COMPONENT NOTIFIED");

	//if (m_pListenerBehaviour) 
	for (int i = 0; i < m_pListeners.size(); ++i)
	{
		m_pListeners[i]->OnCollision(entity);// TODO: pass entity that you're colliding with
	}
}

ColliderComponent::ColliderComponent(Entity* parent, std::unique_ptr<Collider> collider):
	Component{ "co_col", parent },
	m_Collider{ std::move(collider) }
{
	
	m_Collider->SetParent(this);
	G_SimulationSystem.RegisterComponent(this);
}

ColliderComponent::~ColliderComponent()
{
	G_SimulationSystem.UnregisterComponent(this);
}

void ColliderComponent::SetCollider(std::unique_ptr<Collider> collider) noexcept
{
	m_Collider = std::move(collider);
}

Collider* ColliderComponent::GetCollider() const noexcept
{
	return m_Collider.get();
}

bool Blade::ColliderComponent::IsActive() const noexcept
{
	return m_activeFlag;
}

void Blade::ColliderComponent::SetCollisionResponseFlag(bool flag) noexcept
{
	m_activeFlag = flag;
}

void Blade::ColliderComponent::AddListener(BehaviourComponent * listener) noexcept
{

	m_pListeners.push_back(listener);
	//m_pListenerBehaviour = listener;
}
