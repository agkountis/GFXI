#include "collider_component.h"
#include "entity.h"
#include "simulation_system.h"
#include "engine_context.h"


using namespace Blade;

ColliderComponent::ColliderComponent(Entity* parent, std::unique_ptr<Collider> collider):
	Component{ "co_col", parent },
	m_Collider{ std::move(collider) }
{
	m_Collider->SetParent(this);
	//#needtoimplement registration to the simulation system passing by the engine context
}

ColliderComponent::~ColliderComponent()
{
	//#needtoimplement un registration to the simulation system passing by the engine context
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
