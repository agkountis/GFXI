#include "engine_context.h"
#include "simulation_component.h"

using namespace Blade;


SimulationComponent::SimulationComponent(Entity* parent, float mass):
	Component("co_sim", parent),
	m_Mass{mass},
	m_InverseMass{1.0f/m_Mass}
{
	EngineContext::GetSimulationSystem().RegisterComponent(this);
}

SimulationComponent::~SimulationComponent()
{
	EngineContext::GetSimulationSystem().UnregisterComponent(this);
}

void SimulationComponent::AddForce(const Vec3f& force) noexcept
{
	m_Force += force;
}

void SimulationComponent::SetForce(const Vec3f& force) noexcept
{
	m_Force = force;
}

void Blade::SimulationComponent::SetPreviousForce(const Vec3f& force) noexcept
{
	m_PrevForce = m_Force;
}

const Vec3f& Blade::SimulationComponent::GetForce() const noexcept
{
	return m_Force;
}

const Blade::Vec3f& Blade::SimulationComponent::GetPreviousForce() const noexcept
{
	return m_PrevForce;
}

void SimulationComponent::ResetForce() noexcept
{
	m_Force = Vec3f{};
}

void SimulationComponent::SetVelocity(const Vec3f& velocity) noexcept
{
	m_Velocity = velocity;
}

void Blade::SimulationComponent::SetPreviousVelocity(const Vec3f& velocity) noexcept
{
	m_PrevVel = velocity;
}

const Vec3f& Blade::SimulationComponent::GetVelocity() const noexcept
{
	return m_Velocity;
}

const Blade::Vec3f& Blade::SimulationComponent::GetPreviousVelocity() const noexcept
{
	return m_PrevVel;
}

void Blade::SimulationComponent::SetPreviousPosition(const Vec3f & position) noexcept
{
	m_PrevPos = position;
}

const Vec3f & Blade::SimulationComponent::GetPreviousPosition() const noexcept
{
	return m_PrevPos;
}

bool Blade::SimulationComponent::IsActive() const noexcept
{
	return m_IsActive;
}

void Blade::SimulationComponent::SetActive(bool active) noexcept
{
	m_IsActive = active;
}

float SimulationComponent::GetMass() const noexcept
{
	return m_Mass;
}

float SimulationComponent::GetInverseMass() const noexcept
{
	return m_InverseMass;
}

