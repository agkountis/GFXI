#pragma once
#include<component.h>
class Entity;
class ColliderComponent // will inherit from component, but after we sort out the behaviours and stuff
{

private:
	Entity* m_pParent;
	bool m_CollisionResponse;
public:
	ColliderComponent(Entity* parent);
	ColliderComponent(ColliderComponent&) = delete;
	ColliderComponent& operator=(ColliderComponent&) = delete;

	~ColliderComponent();


};

