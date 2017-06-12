#include "emitter_component.h"
#include "math_utils.h"
#include "entity.h"
#include <algorithm>
#include "engine_context.h"
#include "component.h"
#include "string_utils.h"
#include "trace.h"
#include "cfg.h"

#ifdef BLADE_BUILD_D3D
#include "d3d/D3D11_texture.h"
#endif

#undef min
#undef max

namespace Blade
{
	// EmitterDescriptor functions ------------------------------------------------------------------
	bool EmitterDescriptor::Load(const std::wstring& file_name) noexcept
	{
		std::string fileName{ StringUtils::ToString(file_name) };

		ConfigFile cfg;

		cfg.Open(fileName.c_str());

		if (!cfg.IsOpen())
		{
			BLADE_ERROR("Failed to parse configuration file: " + fileName);
			return false;
		}

		velocity = cfg.GetVec4f("emitter.initialVelocity").xyz;
		externalForce = cfg.GetVec4f("emitter.externalForce").xyz;
		spawnRate = cfg.GetFloat("emitter.spawnRate");
		lifespan = cfg.GetFloat("emitter.lifespan");
		maxParticles = cfg.GetFloat("emitter.maxParticles");
		spawnRadius = cfg.GetFloat("emitter.spawnRadius");
		particleSize = cfg.GetFloat("emitter.particleSize");
		startColor = cfg.GetVec4f("emitter.startColor");
		endColor = cfg.GetVec4f("emitter.endColor");

		std::string texFileName{ cfg.GetString("emitter.textureFileName") };

#ifdef BLADE_BUILD_D3D
		texture = G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + StringUtils::ToWstring(texFileName));
		texture->SetTextureType(TEX_DIFFUSE);
#else
#endif

		std::string blendState{ cfg.GetString("emitter.blendState") };

		if (blendState == "additive")
		{
			blendStateType = RenderStateType::BS_BLEND_ADDITIVE;
		}
		else if (blendState == "alpha")
		{
			blendStateType = RenderStateType::BS_BLEND_ALPHA;
		}
		else
		{
			BLADE_ERROR("Emitter configuration loading failed! Blend state can only be 'additive' or 'alpha'.");
			return false;
		}

		velocityRange = cfg.GetFloat("emitter.velocityRange");

		std::string activeStr{ cfg.GetString("emitter.active") };

		if (activeStr == "true")
		{
			active = true;
		}
		else if (activeStr == "false")
		{
			active = false;
		}
		else
		{
			BLADE_ERROR("Emmiter configuration loading failed! Active can only be 'true' or 'false'");
			return false;
		}

		return true;
	}
	// ----------------------------------------------------------------------------------------------

	EmitterComponent::EmitterComponent(Entity * parent):
		BehaviourComponent("co_emitter", parent),
		m_pMesh{nullptr}
	{

		m_Descriptor.spawnRate = 1.0f;
		m_Descriptor.lifespan = 1.0f;
		m_Descriptor.maxParticles = 1;
		m_Descriptor.spawnRadius = 0.0f;
		m_Descriptor.particleSize = 1.0f;
		m_Descriptor.particlesToSpawn = 0;
		m_Descriptor.active = true;
		m_Descriptor.velocityRange = 0.0f;

		G_ParticleSystem.RegisterComponent(this);
	}

	EmitterComponent::EmitterComponent(Entity * entity, const EmitterDescriptor& descriptor):
		BehaviourComponent("co_emitter",entity),
		m_Descriptor(descriptor)
	{
		G_ParticleSystem.RegisterComponent(this);
	}

	EmitterComponent::~EmitterComponent()
	{
		G_ParticleSystem.UnregisterComponent(GetId());
	}

	void EmitterComponent::KillAndUpdateParticles(double tsec, const float dt) noexcept
	{
		auto it{ m_Particles.begin() };
		while (it != m_Particles.end())
		{
			auto& p = *it;

			if (!p.active)
			{
				it = m_Particles.erase(it);
				continue;
			}

			double t{ (tsec - p.spawn_time) / m_Descriptor.lifespan };

			UpdateParticleColor(t, p.color);

			UpdatePhysics(dt, p);

			if (p.life < 0.0f)
			{
				p.active = false;
			}

			++it;
		}
	}

	void EmitterComponent::UpdateParticleColor(double t, Vec4f & color) const noexcept
	{
		float min_x{ std::min(m_Descriptor.startColor.x, m_Descriptor.endColor.x) };
		float max_x{ std::max(m_Descriptor.startColor.x, m_Descriptor.endColor.x) };

		float min_y{ std::min(m_Descriptor.startColor.y, m_Descriptor.endColor.y) };
		float max_y{ std::max(m_Descriptor.startColor.y, m_Descriptor.endColor.y) };

		float min_z{ std::min(m_Descriptor.startColor.z, m_Descriptor.endColor.z) };
		float max_z{ std::max(m_Descriptor.startColor.z, m_Descriptor.endColor.z) };

		float min_w{ std::min(m_Descriptor.startColor.w, m_Descriptor.endColor.w) };
		float max_w{ std::max(m_Descriptor.startColor.w, m_Descriptor.endColor.w) };

		Vec4f col;

		col.x = m_Descriptor.startColor.x + (m_Descriptor.endColor.x - m_Descriptor.startColor.x) * static_cast<float>(t);
		col.y = m_Descriptor.startColor.y + (m_Descriptor.endColor.y - m_Descriptor.startColor.y) * static_cast<float>(t);
		col.z = m_Descriptor.startColor.z + (m_Descriptor.endColor.z - m_Descriptor.startColor.z) * static_cast<float>(t);
		col.w = m_Descriptor.startColor.w + (m_Descriptor.endColor.w - m_Descriptor.startColor.w) * static_cast<float>(t);

		col.x = std::max<float>(min_x, std::min<float>(col.x, max_x));
		col.y = std::max<float>(min_y, std::min<float>(col.y, max_y));
		col.z = std::max<float>(min_z, std::min<float>(col.z, max_z));
		col.w = std::max<float>(min_w, std::min<float>(col.w, max_w));

		color = col;
	}

	void EmitterComponent::UpdatePhysics(float dt, Particle & p) const noexcept
	{
		p.position += p.velocity * dt;
		p.velocity += m_Descriptor.externalForce * dt;
		p.life -= dt;
	}

	void EmitterComponent::EmitParticles(const float dt, double tsec) noexcept
	{
		m_Descriptor.particlesToSpawn += m_Descriptor.spawnRate * dt;
		int numSpawn = m_Descriptor.particlesToSpawn;
		m_Descriptor.particlesToSpawn -= numSpawn;

		int i{ 0 };

		if (m_Descriptor.active)
		{
			while (i < numSpawn && m_Particles.size() < m_Descriptor.maxParticles) {

				float randPosX = static_cast<float>(rand()) /
					static_cast<float>(RAND_MAX) * m_Descriptor.spawnRadius * 2.0f - m_Descriptor.spawnRadius;
				float randPosY = static_cast<float>(rand()) /
					static_cast<float>(RAND_MAX) * m_Descriptor.spawnRadius * 2.0f - m_Descriptor.spawnRadius;
				float randPosZ = static_cast<float>(rand()) /
					static_cast<float>(RAND_MAX) * m_Descriptor.spawnRadius * 2.0f - m_Descriptor.spawnRadius;

				float randVelX = static_cast<float>(rand()) /
					static_cast<float>(RAND_MAX) * m_Descriptor.velocityRange * 2.0f - m_Descriptor.velocityRange;
				float randVelY = static_cast<float>(rand()) /
					static_cast<float>(RAND_MAX) * m_Descriptor.velocityRange * 2.0f - m_Descriptor.velocityRange;
				float randVelZ = static_cast<float>(rand()) /
					static_cast<float>(RAND_MAX) * m_Descriptor.velocityRange * 2.0f - m_Descriptor.velocityRange;

				Particle p;
				p.position = (GetParent()->GetXform() * Vec4f { 0.0f, 0.0f, 0.0f, 1.0f }).xyz + Vec3f{ randPosX, randPosY, randPosZ };
				p.velocity = m_Descriptor.velocity + Vec3f{ randVelX, randVelY, randVelZ };
				p.life = m_Descriptor.lifespan;
				p.color = m_Descriptor.startColor;
				p.spawn_time = tsec;
				p.size = m_Descriptor.particleSize;
				p.active = true;

				m_Particles.push_back(p);

				++i;
			}
		}
	}

	const std::vector<Particle>& EmitterComponent::GetParticles() const noexcept
	{
		return m_Particles;
	}

	const EmitterDescriptor& EmitterComponent::GetEmitterDescriptor() const noexcept
	{
		return m_Descriptor;
	}

	void EmitterComponent::SetDescriptor(const EmitterDescriptor& descriptor) noexcept
	{
		m_Descriptor = descriptor;
	}

	float EmitterComponent::GetSpawnRate() const noexcept
	{
		return m_Descriptor.spawnRate;
	}

	void EmitterComponent::SetSpawnRate(const float spawnRate) noexcept
	{
		m_Descriptor.spawnRate = spawnRate;
	}

	float EmitterComponent::GetLifeSpan() const noexcept
	{
		return m_Descriptor.lifespan;
	}

	void EmitterComponent::SetLifeSpan(const float lifespan) noexcept
	{
		m_Descriptor.lifespan = lifespan;
	}

	float EmitterComponent::GetMaxParticles() const noexcept
	{
		return m_Descriptor.maxParticles;
	}

	void EmitterComponent::SetMaxParticles(const float maxParticles) noexcept
	{
		m_Descriptor.maxParticles = maxParticles;
	}

	float EmitterComponent::GetSpawnRadius() const noexcept
	{
		return m_Descriptor.spawnRadius;
	}

	void EmitterComponent::SetSpawnRadius(const float spawnRadius) noexcept
	{
		m_Descriptor.spawnRadius = spawnRadius;
	}

	float EmitterComponent::GetParticleSize() const noexcept
	{
		return m_Descriptor.particleSize;
	}

	void EmitterComponent::SetParticleSize(const float particleSize) noexcept
	{
		m_Descriptor.particleSize = particleSize;
	}

	const Vec4f& EmitterComponent::GetStartColor() const noexcept
	{
		return m_Descriptor.startColor;
	}

	void EmitterComponent::SetStartColor(const Vec4f& startColor)  noexcept
	{
		m_Descriptor.startColor = startColor;
	}

	const Vec4f& EmitterComponent::GetEndColor() const noexcept
	{
		return m_Descriptor.endColor;
	}

	void EmitterComponent::SetEndColor(const Vec4f& endColor)  noexcept
	{
		m_Descriptor.endColor = endColor;
	}

	bool EmitterComponent::IsActive() const noexcept
	{
		return m_Descriptor.active;
	}

	void EmitterComponent::SetActive(const bool active) noexcept
	{
		m_Descriptor.active = active;
	}

	const Vec3f& EmitterComponent::GetVelocity() const noexcept
	{
		return m_Descriptor.velocity;
	}

	void EmitterComponent::SetVelocity(const Vec3f& velocity) noexcept
	{
		m_Descriptor.velocity = velocity;
	}

	float EmitterComponent::GetVelocityRange() const noexcept
	{
		return m_Descriptor.velocityRange;
	}

	void EmitterComponent::SetVelocityRange(const float velocityRange) noexcept
	{
		m_Descriptor.velocityRange = velocityRange;
	}

	const Vec3f& EmitterComponent::GetExternalForce() const noexcept
	{
		return m_Descriptor.externalForce;
	}

	void EmitterComponent::SetExternalForce(const Vec3f& externalFroce) noexcept
	{
		m_Descriptor.externalForce = externalFroce;
	}

	Mesh* EmitterComponent::GetMesh() const noexcept
	{
		return m_pMesh;
	}

	void EmitterComponent::SetMesh(Mesh* mesh) noexcept
	{
		m_pMesh = mesh;
	}

	Texture* EmitterComponent::GetTexture() const noexcept
	{
		return m_Descriptor.texture;
	}

	void EmitterComponent::SetTexture(Texture* texture) noexcept
	{
		m_Descriptor.texture = texture;
	}

	RenderStateType EmitterComponent::GetBlendStateType() const noexcept
	{
		return m_Descriptor.blendStateType;
	}

	void EmitterComponent::SetBlendStateType(RenderStateType blendStateType) noexcept
	{
		m_Descriptor.blendStateType = blendStateType;
	}

	void EmitterComponent::Update(const float dt, const long time /* =0*/) noexcept
	{
		double tsec{ time / 1000.0 };

		KillAndUpdateParticles(tsec, dt);

		EmitParticles(dt, tsec);
	}

	void EmitterComponent::Setup() noexcept
	{
		//Nothing to setup
		int a{ 3 };
		a++;
	}

	void EmitterComponent::Teardown() noexcept
	{
		//Nothing to destroy
	}

}