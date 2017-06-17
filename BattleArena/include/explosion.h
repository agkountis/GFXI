#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "entity.h"
#include "emitter_component.h"

class Explosion : public Blade::Entity
{
private:
	static int s_Counter;

	 Blade::EmitterDescriptor m_ParticleDescriptor;
public:
	Explosion(float lifeTimeInSeconds);
	~Explosion();

	void RegisterWithScene();
};

#endif