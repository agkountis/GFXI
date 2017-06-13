#ifndef BULLET_BEHAVIOUR_H_
#define BULLET_BEHAVIOUR_H_
#include "behaviour_component.h"
#include "entity.h"

class BulletBehaviour : public Blade::BehaviourComponent
{
private:
	//local or not

public:
	BulletBehaviour(Blade::Entity* parent);

	void Update(const float dt, const long time = 0) noexcept override;

	void Setup() noexcept override;

	void Teardown() noexcept override;

	void OnCollision(Blade::Entity* other) noexcept override;



};


#endif