#ifndef BLADE_EMITTER_COMPONENT_H_
#define BLADE_EMITTER_COMPONENT_H_

#include "behaviour_component.h"
#include <vector>
#include "mesh.h"
#include "material.h"

namespace Blade
{
	/*
	\brief Represents a particle of the particle system
	*/
	struct Particle
	{
		Vec3f position;
		Vec4f color;
		float size;

		Vec3f velocity;
		float life;
		bool active;

		double spawn_time;
	};

	/*
	\brief Emitter component is a behaviour component of the engine that 
	can emit particles. EmitterComponents are used inside by the particle system.
	*/
	class EmitterComponent : public BehaviourComponent
	{
	public:
		/*
		\brief Descriptor of the emitter.
		\details Stores all the information relevant to the emitter.
		*/
		struct EmitterDescriptor
		{
			/*
			\details Material of the particle that this emitter will spawn.
			*/
			Material material;
			/*
			\details Cache of the current velocity of the emitter
			*/
			Vec3f velocity;

			/*
			\details Cache external velocity of the emitter
			*/
			Vec3f externalForce;

			float spawnRate;
			float lifespan;
			float maxParticles;
			float spawnRadius;

			float particleSize;

			Vec4f startColor;
			Vec4f endColor;

			float particlesToSpawn;
			float velocityRange;

			bool active;
		};

	private:
		/*
		\details Vectors of particles of this emitter
		*/
		std::vector<Particle> m_Particles;

		/*
		\details The descriptor of this emitter 
		*/
		EmitterDescriptor m_Descriptor;

		/*
		\details Mesh of the particle that this emitter will spawn.
		*/
		Mesh* m_pMesh;



	public:
		explicit EmitterComponent(Entity* parent);
		explicit EmitterComponent(Entity* entity, const EmitterDescriptor& descriptor);
		EmitterComponent(const EmitterComponent& other) = default;
		EmitterComponent& operator=(const EmitterComponent& other) = default;

		~EmitterComponent();

		/*
		\brief Update the particles owned by this emitter.
		\details The particle loop implemented is: kill particles -> update
		*/
		void Update(const float dt, const long time /* =0*/) noexcept override;

		void Setup() noexcept override;

		void Teardown() noexcept override;

		//////////////////////////////////////////////////////////////////////////
		// Getters and setters
		//////////////////////////////////////////////////////////////////////////

		const std::vector<Particle>& GetParticles() const noexcept
		{
			return m_Particles;
		}

		const EmitterDescriptor& GetEmitterDescriptor() const noexcept
		{
			return m_Descriptor;
		}

		void SetDescriptor(const EmitterDescriptor& descriptor) noexcept
		{
			m_Descriptor = descriptor;
		}

		float GetSpawnRate() const noexcept
		{
			return m_Descriptor.spawnRate;
		}

		void SetSpawnRate(const float spawnRate) noexcept
		{
			m_Descriptor.spawnRate = spawnRate;
		}

		float GetLifeSpan() const noexcept
		{
			return m_Descriptor.lifespan;
		}

		void SetLifeSpan(const float lifespan) noexcept
		{
			m_Descriptor.lifespan = lifespan;
		}

		float GetMaxParticles() noexcept
		{
			return m_Descriptor.maxParticles;
		}

		void SetMaxParticles(const float maxParticles) noexcept
		{
			m_Descriptor.maxParticles = maxParticles;
		}

		float GetSpawnRadius() noexcept
		{
			return m_Descriptor.spawnRadius;
		}

		void SetSpawnRadius(const float spawnRadius) noexcept
		{
			m_Descriptor.spawnRadius = spawnRadius;
		}

		float GetParticleSize() noexcept
		{
			return m_Descriptor.particleSize;
		}

		void SetParticleSize(const float particleSize) noexcept
		{
			m_Descriptor.particleSize = particleSize;
		}

		const Vec4f& GetStartColor() const noexcept
		{
			return m_Descriptor.startColor;
		}

		void SetStartColor(const Vec4f& startColor)  noexcept
		{
			m_Descriptor.startColor = startColor;
		}

		const Vec4f& GetEndColor() const noexcept
		{
			return m_Descriptor.endColor;
		}

		void SetEndColor(const Vec4f& endColor)  noexcept
		{
			m_Descriptor.endColor = endColor;
		}

		bool IsActive() const noexcept
		{
			return m_Descriptor.active;
		}

		void SetActive(const bool active) noexcept
		{
			m_Descriptor.active = active;
		}

		const Vec3f& GetVelocity() const noexcept
		{
			return m_Descriptor.velocity;
		}

		void SetVelocity(const Vec3f& velocity) noexcept
		{
			m_Descriptor.velocity = velocity;
		}

		float GetVelocityRange() const noexcept
		{
			return m_Descriptor.velocityRange;
		}

		void SetVelocityRange(const float velocityRange) noexcept
		{
			m_Descriptor.velocityRange = velocityRange;
		}

		const Vec3f& GetExternalForce() const noexcept
		{
			return m_Descriptor.externalForce;
		}

		void SetExternalForce(const Vec3f& externalFroce) noexcept
		{
			m_Descriptor.externalForce = externalFroce;
		}

		Mesh* GetMesh() const noexcept
		{
			return m_pMesh;
		}

		void SetMesh(Mesh* mesh) noexcept
		{
			m_pMesh = mesh;
		}

		const Material& GetMaterial() const noexcept
		{
			return m_Descriptor.material;
		}

		void SetMaterial(const Material& material) noexcept
		{
			m_Descriptor.material = material;
		}	
	private:
		void EmitParticles(const float dt, double tsec) noexcept;

		void KillAndUpdateParticles(double tsec, const float dt) noexcept;

		void UpdateParticleColor(double t, Vec4f& color) const noexcept;
		
		void UpdatePhysics(float  dt, Particle& p) const noexcept;

	};

}

#endif