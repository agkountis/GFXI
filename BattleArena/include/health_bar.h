#ifndef HEALTH_BAR_H_
#define HEALTH_BAR_H_

#include "entity.h"
#include "render_component.h"

#include "camera.h"

class HealthBar: public Blade::Entity
{
private:
	static Blade::Camera* s_pCurrentCamera;
	Blade::Entity* m_pEmptyBar{ nullptr };
	Blade::Entity* m_pFullBar{ nullptr };
	int m_MaxHealth;

public:
	HealthBar(Blade::Entity* parent,Blade::Entity* emptyBar, Blade::Entity* fullBar, int maxHealthValue);
	void SetHealthValue(int healthValue) const;
	static void SetCurrentCamera();
	void Update(float dt, long time /*= 0*/) noexcept override;

};

#endif
