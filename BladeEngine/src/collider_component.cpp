#include "collider_component.h"



ColliderComponent::ColliderComponent(Entity* parent):
	m_pParent(parent),
	m_CollisionResponse{true}
{
}


ColliderComponent::~ColliderComponent()
{
}
