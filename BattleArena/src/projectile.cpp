#include "projectile.h"
#include "render_component.h"
#include "simulation_component.h"
#include "collider_component.h"
#include "bounding_sphere.h"
#include "mesh.h"
#include "engine_context.h"
#include "emitter_component.h"
#include "d3d/D3D11_texture.h"
#include "test_behaviour.h"
#include "bullet_behaviour.h"

using namespace Blade;

Projectile::Projectile(const std::string& name,
               const std::wstring& mesh,
               const Material& material,
               const float radius,
               const float mass,
               const Vec3f& position,
               const Vec3f& velocity) : Entity(name), m_Radius{radius}, m_Active{false}
{

	SetScale(Vec3f(radius, radius, radius));
	SetPosition(position);
	RenderComponent* rc{ new RenderComponent{ this } };
	rc->SetMesh(G_ResourceManager.Get<Mesh>(mesh));
	rc->SetMaterial(material);
	SimulationComponent* simC{ new SimulationComponent{ this ,mass } };
	simC->SetVelocity(velocity);
//#if !_DEBUG
	EmitterComponent* ec = new EmitterComponent{ this };
	ec->SetLifeSpan(1.0f);
	ec->SetMaxParticles(1000);
	ec->SetSpawnRate(200);
	ec->SetActive(true);
	ec->SetParticleSize(0.8f);
	ec->SetSpawnRadius(m_Radius);
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
//#endif
	m_Timer.Start();
	//auto bv{ new BulletBehaviour{ this } };
	//colC->AddListener(bv);
}

void Projectile::Update(float dt, long time /*= 0*/) noexcept
{
	if(!m_Active)
	{
		if (m_Timer.GetMsec() > 50)
		{
			ColliderComponent* colC{ new ColliderComponent{ this,std::make_unique<BoundingSphere>(m_Radius) } };
			auto bv{ new BulletBehaviour{ this } };
			colC->AddListener(bv);
			m_Active = true;
		}
	}
}
