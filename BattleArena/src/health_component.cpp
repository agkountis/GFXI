#include "health_component.h"
#include "trace.h"
#include "projectile.h"
using namespace Blade;


HealthComponent::HealthComponent(Entity* parent):
BehaviourComponent("co_health", parent)
{
	m_Timer.Start();
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
	if(dynamic_cast<Projectile*>(other))
	{
		if (m_Timer.GetMsec() > m_CollisionTimeOffset)
		{
			BLADE_TRACE(GetParent()->GetName() + " - " + std::to_string(m_HealthValue));

			//Collision detected
			if (m_HealthValue > 0)
			{
				m_HealthValue -= m_Damage;
				if (m_pListenerBar)
				{
					m_pListenerBar->SetHealthValue(m_HealthValue);
				}
			}
			else if (m_HealthValue <= 0)
			{
				GetParent()->SetAlive(false);
			}
			

			m_Timer.Reset();
		}

	}
}

int HealthComponent::GetHealthValue() const noexcept
{
	return m_HealthValue;
}

void HealthComponent::SetListenerBar(HealthBar * healthBar)
{
	m_pListenerBar = healthBar;
}
