#include "bullet.h"
#include "render_component.h"
#include "simulation_component.h"
#include "collider_component.h"
#include "bounding_sphere.h"
#include "mesh.h"
#include "engine_context.h"
#include "emitter_component.h"
#include "d3d/D3D11_texture.h"
#include "test_behaviour.h"

using namespace Blade;

Bullet::Bullet(const std::string& name,
               const std::wstring& mesh,
               const Material& material,
               const float radius,
               const float mass,
               const Vec3f& position,
               const Vec3f& velocity) : Entity(name)
{
	SetPosition(position);
	RenderComponent* rc{ new RenderComponent{ this } };
	rc->SetMesh(G_ResourceManager.Get<Mesh>(mesh));
	rc->SetMaterial(material);
	SimulationComponent* simC{ new SimulationComponent{ this ,mass } };
	ColliderComponent* colC{ new ColliderComponent{ this,std::make_unique<BoundingSphere>(radius) } };
	EmitterComponent* ec = new EmitterComponent{ this };
	ec->SetLifeSpan(1.0f);
	ec->SetMaxParticles(1000);
	ec->SetSpawnRate(200);
	ec->SetActive(true);
	ec->SetParticleSize(3.f);
	ec->SetSpawnRadius(1.5f);
	ec->SetVelocity(Vec3f{ 0.0f, 1.0f, 0.0f });
	ec->SetVelocityRange(1.3f);
	ec->SetExternalForce(Vec3f{ 0.0f, -1.3f, 0.0f });
	ec->SetMesh(G_ResourceManager.Get<Mesh>(L"plane"));
	ec->SetStartColor(Vec4f{ 1.0f, 1.0f, 1.0f, 1.0f });
	ec->SetEndColor(Vec4f{ 1.0f, 1.0f, 1.0f, 0.1f });
	ec->SetBlendStateType(RenderStateType::BS_BLEND_ADDITIVE);
	Texture* tex{ G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"expl02.png") };
	tex->SetTextureType(TEX_DIFFUSE);
	ec->SetTexture(tex);

	TestBehaviour* tb{ new TestBehaviour{ this } };
	colC->AddListener(tb);

	simC->SetVelocity(velocity);
}
