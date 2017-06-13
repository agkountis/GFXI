#include "health_bar.h"





HealthBar::HealthBar(Blade::Entity * parent, int maxHealthValue):
	Entity("HealthBar of " + parent->GetName())
{
	this->SetParent(parent);
}

HealthBar::~HealthBar()
{
}
