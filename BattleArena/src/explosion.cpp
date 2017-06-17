#include "explosion.h"
#include "engine_context.h"
#include "d3d\D3D11_texture.h"
#include "explosion_behaviour.h"

using namespace Blade;

int Explosion::s_Counter{ 0 };


Explosion::Explosion(float lifeTimeInSeconds):Entity("Explosion " + std::to_string(s_Counter))
{
	s_Counter++;


	m_ParticleDescriptor.active = true;
	m_ParticleDescriptor.lifespan = 1.0f;
	m_ParticleDescriptor.maxParticles = 500.0f;
	m_ParticleDescriptor.spawnRate = 3000.0f;
	m_ParticleDescriptor.particleSize = 2.0f;
	m_ParticleDescriptor.velocity = Vec3f(0.1f, 1.1f, 0.1f);
	m_ParticleDescriptor.velocityRange = 12.0f;
	m_ParticleDescriptor.startColor = Vec4f(0.5f, 0.5f, 0.0f, 1.0f);
	m_ParticleDescriptor.endColor = Vec4f(1.0f, 0.1f, 0.0f, 0.1f);
	m_ParticleDescriptor.blendStateType = RenderStateType::BS_BLEND_ADDITIVE;
	m_ParticleDescriptor.externalForce = Vec3f(-0.0f, 2.5f, 0.5f);
	m_ParticleDescriptor.particlesToSpawn = 400.0f;
	m_ParticleDescriptor.spawnRadius = 2.0f;

	auto emc{ new EmitterComponent{ this, m_ParticleDescriptor } };
	Texture* tex{ G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"star.jpg") };
	tex->SetTextureType(TEX_DIFFUSE);
	emc->SetTexture(tex);
	emc->SetMesh(G_ResourceManager.Get<Mesh>(L"plane"));
	auto bc = new ExplosionBehaviour(this,lifeTimeInSeconds);

}


Explosion::~Explosion()
{
}

void Explosion::RegisterWithScene()
{
	G_SceneManager.GetCurrentScene()->AddEntity(this);
}
