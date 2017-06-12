#include "health_component.h"
#include "trace.h"
using namespace Blade;


HealthComponent::HealthComponent(Entity* parent):
BehaviourComponent("co_health", parent)
{
	m_Timer.Start();
}


HealthComponent::~HealthComponent()
{
}

void HealthComponent::Update(const float dt, const long time) noexcept
{
}

void HealthComponent::Setup() noexcept
{
}

void HealthComponent::Teardown() noexcept
{
}

void HealthComponent::OnCollision(Entity * other) noexcept
{
	if (m_Timer.GetMsec() > m_CollisionTimeOffset)
	{
		//Collision detected
		if (m_HealthValue > 0) m_HealthValue -= m_Damage;
		if (m_HealthValue < 0) m_HealthValue = 0;
		BLADE_TRACE("HEALTH COMPONENT - HIT, CURRENT VALUE IS: " + std::to_string(m_HealthValue));
		m_Timer.Reset();
	}

}

int HealthComponent::GetHealthValue()
{
	return m_HealthValue;
}
