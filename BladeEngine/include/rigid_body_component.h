#pragma once

#include "component.h"
class Entity;
class RigidBodyComponent // will inherit from component, but after we sort out the behaviours and stuff
{
public:
	RigidBodyComponent(Entity* parent);

	RigidBodyComponent(RigidBodyComponent&) = delete;
	RigidBodyComponent& operator=(RigidBodyComponent&) = delete;
	~RigidBodyComponent();

private:
	Entity* m_pParent;
	//TO DO: Add all relevant members

};

