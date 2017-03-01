#ifndef BLADE_SIMULATION_SYSTEM_H_
#define BLADE_SIMULATION_SYSTEM_H_

#include "System.h"
#include "collider_component.h"
#include "rigid_body_component.h"
class SystemSimulation: Blade::System
{
private:
	SystemSimulation(); // Do not allow user to create instance of the class!

public:
	SystemSimulation& operator=(SystemSimulation&) = delete;
	SystemSimulation(SystemSimulation&) = delete;
	~SystemSimulation(); 


	/**
	* \brief Performs system initialization.
	* \return TRUE if initialization is successfull, FALSE otherwise.
	*/
	bool Initialize() noexcept;

	/**
	* \brief Updates physics simulation.
	* \param deltaTime The time elapsed from the previous frame of the application.
	*/
	void Process(float deltaTime) noexcept;

	//TO DO: add register and unregistered methods
};

#endif //BLADE_SIMULATION_SYSTEM_H_