#ifndef HEALTH_BAR_FACTORY_H_
#define HEALTH_BAR_FACTORY_H_

#include "health_bar.h"
class GameScene;

class HealthBarFactory
{
public:
	HealthBar* CreateHealthBar(Blade::Entity* parent, int maxHealthValue);
};

#endif