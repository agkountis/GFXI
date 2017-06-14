#include "health_bar.h"
#include "trace.h"
using namespace Blade;

HealthBar::HealthBar(Entity* parent, Entity* emptyBar, Entity* fullBar, int maxHealthValue):
	Entity("HealthBar of " + parent->GetName()),
	m_pEmptyBar{emptyBar},
	m_pFullBar{fullBar},
	m_MaxHealth{maxHealthValue}
{
	parent->AddChild(this);
	
	this->AddChild(m_pEmptyBar);
	this->AddChild(m_pFullBar);

}


void HealthBar::SetHealthValue(int healthValue) const
{

	if (healthValue > m_MaxHealth) healthValue = m_MaxHealth;
	if (healthValue < 0) healthValue = 0;

	float percentage = static_cast<float>(healthValue) / static_cast<float>(m_MaxHealth);
	float maxBarScale = 4.0f;
	
	Vec3f scale = m_pFullBar->GetScale();
	scale.x =  maxBarScale*percentage;

	Vec3f pos = m_pFullBar->GetLocalPosition();

	pos.x =  - maxBarScale*(1-percentage)*0.5f;

	m_pFullBar->SetScale(scale);
	m_pFullBar->SetPosition(pos);

}
