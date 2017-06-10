#include "bullet.h"
#include "render_component.h"
#include "simulation_component.h"
#include "collider_component.h"
#include "bounding_sphere.h"
#include "mesh.h"
#include "engine_context.h"

using namespace Blade;

Bullet::Bullet(const std::string & name, const std::wstring & mesh, const Blade::Material & material, const float radius, const float mass, const Blade::Vec3f & position, const Blade::Vec3f & velocity):
	Entity(name)
{
	SetPosition(position);
	RenderComponent* rc{ new RenderComponent{ this } };
	rc->SetMesh(G_ResourceManager.Get<Mesh>(mesh));
	rc->SetMaterial(material);
	SimulationComponent* simC{ new SimulationComponent{ this ,mass} };
	ColliderComponent* colC{ new ColliderComponent{ this,std::make_unique<BoundingSphere>(radius) } };
	simC->SetVelocity(velocity);
}
