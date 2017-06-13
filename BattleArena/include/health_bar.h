#ifndef HEALTH_BAR_H_
#define HEALTH_BAR_H_

#include "entity.h"

class HealthBar: public Blade::Entity
{
private:
	Blade::Entity* m_pEmptyBar{ nullptr };
	Blade::Entity* m_pFullBar{ nullptr };

public:
	HealthBar(Blade::Entity* parent, int maxHealthValue);
	~HealthBar();
};

#endif
