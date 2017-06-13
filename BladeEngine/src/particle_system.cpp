#include "particle_system.h"
#include "emitter_component.h"
#include <memory>

using namespace Blade;

namespace Blade
{
	void ParticleSystem::RegisterComponent(EmitterComponent * emitterComponent) noexcept
	{
		m_EmitterComponents.push_back(emitterComponent);
	}

	bool ParticleSystem::Initialize() noexcept
	{
		return true;
	}

	void ParticleSystem::Process(float deltaTime/*=.0f*/, long time/*=0*/) noexcept
	{
		//Particle system do not process anything
	}

	void ParticleSystem::UnregisterComponent(const int id) noexcept
	{
		auto it = m_EmitterComponents.begin();

		while (it != m_EmitterComponents.end())
		{
			auto entry = *it;

			if (id == entry->GetId())
			{
				it = m_EmitterComponents.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	std::vector<EmitterComponent*>& ParticleSystem::GetEmitterComponents() noexcept
	{
		return m_EmitterComponents;
	}
}

