#ifndef BULLET_H_
#define BULLET_H_
#include "entity.h"
#include "material.h"
#include "timer.h"
class Projectile : public Blade::Entity
{
public:
	Projectile(const std::string& name,
	       const std::wstring& mesh,
	       const Blade::Material& material,
	       const float radius,
	       const float mass,
	       const Blade::Vec3f& position,
	       const Blade::Vec3f& velocity);
private:
	Blade::Timer m_Timer;
	float m_Radius;
	bool m_Active;
	void Update(float dt, long time = 0) noexcept override;
};

#endif
