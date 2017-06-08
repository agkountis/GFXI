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
	\brief Descriptor of the emitter.
	\details Stores all the information relevant to the emitter.
	*/
	struct EmitterDescriptor : Resource
	{
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

		Texture* texture;

		RenderStateType blendStateType;

		float particlesToSpawn;
		float velocityRange;

		bool active;

		bool Load(const std::wstring& file_name) noexcept override;
	};

	/*
	\brief Emitter component is a behaviour component of the engine that
	can emit particles. EmitterComponents are used inside by the particle system.
	*/
	class EmitterComponent : public BehaviourComponent
	{
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

		void EmitParticles(const float dt, double tsec) noexcept;

		void KillAndUpdateParticles(double tsec, const float dt) noexcept;

		void UpdateParticleColor(double t, Vec4f& color) const noexcept;

		void UpdatePhysics(float  dt, Particle& p) const noexcept;

	public:
		explicit EmitterComponent(Entity* parent);

		explicit EmitterComponent(Entity* entity, const EmitterDescriptor& descriptor);

		EmitterComponent(const EmitterComponent& other) = default;

		EmitterComponent& operator=(const EmitterComponent& other) = default;

		~EmitterComponent();

		const std::vector<Particle>& GetParticles() const noexcept;

		const EmitterDescriptor& GetEmitterDescriptor() const noexcept;

		void SetDescriptor(const EmitterDescriptor& descriptor) noexcept;

		float GetSpawnRate() const noexcept;

		void SetSpawnRate(const float spawnRate) noexcept;

		float GetLifeSpan() const noexcept;

		void SetLifeSpan(const float lifespan) noexcept;

		float GetMaxParticles() const noexcept;

		void SetMaxParticles(const float maxParticles) noexcept;

		float GetSpawnRadius() const noexcept;

		void SetSpawnRadius(const float spawnRadius) noexcept;

		float GetParticleSize() const noexcept;

		void SetParticleSize(const float particleSize) noexcept;

		const Vec4f& GetStartColor() const noexcept;

		void SetStartColor(const Vec4f& startColor) noexcept;

		const Vec4f& GetEndColor() const noexcept;

		void SetEndColor(const Vec4f& endColor) noexcept;

		bool IsActive() const noexcept;

		void SetActive(const bool active) noexcept;

		const Vec3f& GetVelocity() const noexcept;

		void SetVelocity(const Vec3f& velocity) noexcept;

		float GetVelocityRange() const noexcept;

		void SetVelocityRange(const float velocityRange) noexcept;

		const Vec3f& GetExternalForce() const noexcept;

		void SetExternalForce(const Vec3f& externalFroce) noexcept;

		Mesh* GetMesh() const noexcept;

		void SetMesh(Mesh* mesh) noexcept;

		Texture* GetTexture() const noexcept;

		void SetTexture(Texture* texture) noexcept;

		RenderStateType GetBlendStateType() const noexcept;

		void SetBlendStateType(RenderStateType blendStateType) noexcept;

		/*
		\brief Update the particles owned by this emitter.
		\details The particle loop implemented is: kill particles -> update
		*/
		void Update(const float dt, const long time /* =0*/) noexcept override;

		void Setup() noexcept override;

		void Teardown() noexcept override;
	};

}

#endif