#include "particle_system.h"
#include "emitter_component.h"
#include <memory>

using namespace Blade;

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::RegisterComponent(EmitterComponent * emitterComponent) noexcept
{
	m_EmitterComponents.push_back(emitterComponent);
}



bool Blade::ParticleSystem::Initialize() noexcept
{
	return true;
}

void Blade::ParticleSystem::Process(float deltaTime/*=.0f*/, long time/*=0*/) noexcept
{
	//Particle system do not process anything
}

void ParticleSystem::UnregisterComponent(const int id) noexcept
{
	std::remove_if(m_EmitterComponents.begin(),
		m_EmitterComponents.end(),
		[id](EmitterComponent* component)
	{
		return id == component->GetId();
	}
	);
}

std::vector<EmitterComponent*>& ParticleSystem::GetEmitterComponents() noexcept
{
	return std::move(m_EmitterComponents);
}



