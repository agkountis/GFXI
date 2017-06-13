#ifndef HEALTH_BAR_FACTORY_H_
#define HEALTH_BAR_FACTORY_H_

#include "health_bar.h"

class GameScene;
class HealthBarFactory
{
private:
	GameScene* m_pGameScene{ nullptr };
public:
	HealthBarFactory(GameScene* gameScene);
	~HealthBarFactory();

	HealthBar* CreateHealthBar(Blade::Entity* parent, int maxHealthValue);
};

#endif