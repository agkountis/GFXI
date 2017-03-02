#include "SystemSimulation.h"

namespace Blade
{

	/*SystemSimulation::SystemSimulation() :System()
	{
	}*/


	SystemSimulation::~SystemSimulation()
	{
	}

	bool SystemSimulation::Initialize() noexcept
	{
		return true;
	}

	void SystemSimulation::Process(float deltaTime) noexcept
	{
	}

	void SystemSimulation::Register(RigidBodyComponent * rbc) noexcept
	{
	}

	void SystemSimulation::Register(ColliderComponent * col) noexcept
	{
	}

	void SystemSimulation::Unregister(Component * c) noexcept
	{
	}
}