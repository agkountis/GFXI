#ifndef HEALTH_BAR_H_
#define HEALTH_BAR_H_

#include "entity.h"
#include "render_component.h"

class HealthBar: public Blade::Entity
{
private:
	Blade::Entity* m_pEmptyBar{ nullptr };
	Blade::Entity* m_pFullBar{ nullptr };

	int m_MaxHealth;

public:
	HealthBar(Blade::Entity* parent,Blade::Entity* emptyBar, Blade::Entity* fullBar, int maxHealthValue);
	~HealthBar();

	void SetHealthValue(int healthValue);


};

#endif
