#include "health_bar.h"

using namespace Blade;

HealthBar::HealthBar(Entity* parent, Entity* emptyBar, Entity* fullBar, int maxHealthValue):
	Entity("HealthBar of " + parent->GetName()),
	m_pEmptyBar{emptyBar},
	m_pFullBar{fullBar},
	m_MaxHealth{maxHealthValue}
{
	this->SetParent(parent);
	
	this->AddChild(m_pEmptyBar);
	this->AddChild(m_pFullBar);


}

HealthBar::~HealthBar()
{
}

void HealthBar::SetHealthValue(int healthValue)
{
	

}
