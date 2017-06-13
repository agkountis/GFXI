#ifndef BLADE_PARTICLE_SYSTEM_H_
#define BLADE_PARTICLE_SYSTEM_H_
#include "system.h"
#include "emitter_component.h"

namespace Blade 
{
	/*
	\brief A system responsible of storing the EmitterComponents.
	*/
	class ParticleSystem : public System
	{
	private:
		std::vector<EmitterComponent*> m_EmitterComponents;

	public:
		/*
		\brief Registers a EmitterComponent to the ParticleSystem
		\param emitterComponent The component to be registered to the Particle system
		*/
		void RegisterComponent(EmitterComponent* emitterComponent) noexcept;

		/*
		\brief Unregisters a EmitterComponent from the ParticleSystem
		\param id The unique id of the EmitterComponent to be unregistered
		*/
		void UnregisterComponent(const int id) noexcept;

		/*
		\brief Initialize the particle system
		*/
		bool Initialize() noexcept override;

		/*
		\brief Return the current vector with all the emitter components
		*/
		std::vector<EmitterComponent*>& GetEmitterComponents() noexcept;

		/*
		\brief The particle system do no need to process anything.
		*/
		void Process(float deltaTime=.0f, long time=0) noexcept override;

	};
}
#endif