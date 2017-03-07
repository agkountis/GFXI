#include "collider_component.h"
#include "simulation_system.h"
#include "bounding_sphere.h"
#include "bounding_box.h"
#include "bounding_cylinder.h"
#include "entity.h"
#include "render_component.h"
#include "engine_context.h"

namespace Blade
{
	ColliderComponent::ColliderComponent(Entity* parent) :
		Component::Component{ "co_col",parent },//here component is added to entity
		m_CollisionResponse{ true },
		m_pBVolume{ nullptr },
		m_ValidFlag{ false }
	{
	}

	ColliderComponent::ColliderComponent(Entity * parent, BVolumeType type):
		Component::Component{ "co_col",parent },//here component is added to entity
		m_CollisionResponse{ true },
		m_pBVolume{ nullptr },
		m_ValidFlag{ false }
	{
		this->CreateBShape(type);
	}


	ColliderComponent::~ColliderComponent()
	{
		if (m_ValidFlag)
		{
			EngineContext::GetSimulationSystem()->UnregisterComponent(this);
		}
		if (m_pBVolume)
		{
			delete m_pBVolume;
		}
	}

	bool ColliderComponent::CreateBShape(BVolumeType bVolumeType)
	{
		if (m_ValidFlag) return true;

		//Fish out render component, if not found return false - failed to create 
		Component* c = GetParent()->GetComponent("co_render");
		if (!c)
		{
			m_ValidFlag = false;
			return m_ValidFlag;
		}

		// Cast component to render component - if failed return false.
		// This check is here just for completion only, at this point we are sure that we've got render component anyway.

		RenderComponent* rc = dynamic_cast<RenderComponent*>(c);
		if (!rc)
		{
			m_ValidFlag = false;
			return m_ValidFlag;
		}

		switch (bVolumeType)
		{
		  case BVolumeType::Sphere:
		  {
			  BVolume(new BoundingSphere(rc->GetMesh()));
			  m_ValidFlag = true;
			  break;
		  }
		  case BVolumeType::Box:
		  {
			  BVolume(new BoundingBox(rc->GetMesh()));
			  m_ValidFlag = true;
			  break;
		  }
		  case BVolumeType::Cylinder:
		  {
			  BVolume(new BoundingCylinder(rc->GetMesh()));
			  m_ValidFlag = true;
			  break;
		  }
		  default:
		  {
			  m_ValidFlag = false;
			  break;
		  }

		}

		if (m_ValidFlag)
		{
			EngineContext::GetSimulationSystem()->RegisterComponent(this);
		}
		return m_ValidFlag;

	}


	bool ColliderComponent::isValid()
	{
		return m_ValidFlag;
	}
}