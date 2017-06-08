#include "emitter_component.h"
#include "math_utils.h"
#include "entity.h"
#include <algorithm>
#include "engine_context.h"
#include "component.h"

#undef min
#undef max

namespace Blade
{
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
	EmitterComponent::EmitterComponent(Entity * entity, const EmitterComponent::EmitterDescriptor& descriptor):
		BehaviourComponent("co_emitter",entity),
		m_Descriptor(descriptor)
	{
		G_ParticleSystem.RegisterComponent(this);
	}


	EmitterComponent::~EmitterComponent()
	{
		G_ParticleSystem.UnregisterComponent(GetId());
	}

	void EmitterComponent::Update(const float dt, const long time /* =0*/) noexcept
	{
		std::cout << time << std::endl;
		double tsec{ time / 1000.0 };

		KillAndUpdateParticles(tsec, dt);

		EmitParticles(dt, tsec);
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

			UpdatePhysics(dt,p);

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
		m_Descriptor.particlesToSpawn += static_cast<int>( m_Descriptor.spawnRate * dt);
		int num_spawn = m_Descriptor.particlesToSpawn;
		m_Descriptor.particlesToSpawn -= num_spawn;

		int i{ 0 };

		if (m_Descriptor.active)
		{
			while (i < num_spawn && m_Particles.size() < m_Descriptor.maxParticles) {

				float rand_pos_x = static_cast<float>(rand()) /
					static_cast<float>(RAND_MAX) * m_Descriptor.spawnRadius * 2.0f - m_Descriptor.spawnRadius;
				float rand_pos_y = static_cast<float>(rand()) /
					static_cast<float>(RAND_MAX) * m_Descriptor.spawnRadius * 2.0f - m_Descriptor.spawnRadius;
				float rand_pos_z = static_cast<float>(rand()) /
					static_cast<float>(RAND_MAX) * m_Descriptor.spawnRadius * 2.0f - m_Descriptor.spawnRadius;

				float rand_vel_x = static_cast<float>(rand()) /
					static_cast<float>(RAND_MAX) * m_Descriptor.velocityRange * 2.0f - m_Descriptor.velocityRange;
				float rand_vel_y = static_cast<float>(rand()) /
					static_cast<float>(RAND_MAX) * m_Descriptor.velocityRange * 2.0f - m_Descriptor.velocityRange;
				float rand_vel_z = static_cast<float>(rand()) /
					static_cast<float>(RAND_MAX) * m_Descriptor.velocityRange * 2.0f - m_Descriptor.velocityRange;

				Particle p;
				p.position = (GetParent()->GetXform() * Vec4f { 0.0f, 0.0f, 0.0f, 1.0f }).xyz + Vec3f{ rand_pos_x, rand_pos_y, rand_pos_z };
				p.velocity = m_Descriptor.velocity + Vec3f{ rand_vel_x, rand_vel_y, rand_vel_z };
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


	void EmitterComponent::Setup() noexcept
	{
		//Nothing to setup
	}

	void EmitterComponent::Teardown() noexcept
	{
		//Nothing to destroy
	}

}