#ifndef BLADE_SIMULATION_COMPONENT_H_
#define BLADE_SIMULATION_COMPONENT_H_
#include "component.h"

namespace Blade
{
	//Forward declaration
	class Entity;

	/*
	\brief SimulationComponent is the component used to perform linear motion + fake rotations
	*/
	class SimulationComponent : public Component
	{
	private:
		//#needtorefactor change the alignment here 

		/*
		\brief Force accumulator of the object
		*/
		Vec3f m_Force;

		Vec3f m_Velocity;

		Vec3f m_Acceleration;

		/*
		\brief Mass of the simulation component
		*/
		float m_Mass;

		/*
		\brief Inverse mass of the simulation component, used 
		in the integration process.
		*/
		float m_InverseMass;

		/*
		\brief Last frame force accumulator
		*/
		Vec3f m_PrevForce;

		/*
		\brief Last frame velocity
		*/
		Vec3f m_PrevVel;

		/*
		\brief Last frame position
		*/
		Vec3f m_PrevPos;

		/*
		\brief 
		*/
		bool m_IsActive;

	public:
		

		SimulationComponent(Entity* parent, float mass);

		~SimulationComponent();

		void SetAcceleration(const Vec3f& acc) noexcept { m_Acceleration = acc; }

		const Vec3f& GetAcceleration() const noexcept { return m_Acceleration; }

		/*
		\brief Add a new force to the force accumulator
		\param force the new force to add to the accumulator
		*/
		void AddForce(const Vec3f& force) noexcept;

		/*
		\brief Set the force accumulator a value
		\param force the new value of the force accumulator
		*/
		void SetForce(const Vec3f& force) noexcept;

		/*
		\brief Set the last frame force accumulator a value
		\param force the new value of the force accumulator (last frame)
		*/
		void SetPreviousForce(const Vec3f& force) noexcept;

		/*
		\brief Getters of the force accumulator
		\return The force accumulator value (current)
		*/
		const Vec3f& GetForce() const noexcept;

		/*
		\brief Getters of the last frame force accumulator
		\return The force accumulator value (last frame)
		*/
		const Vec3f& GetPreviousForce() const noexcept;

		//#warning check if the reset functionalities also in the system.
		/*
		\brief Clears the force accumulator (current)
		*/
		void ResetForce() noexcept;

		/*
		\brief Set a new velocity for the simulation component
		\param velocity new velocity  (current)
		*/
		void SetVelocity(const Vec3f& velocity) noexcept;

		/*
		\brief Set the last frame velocity for the simulation component
		\param velocity new velocity (last frame)
		*/
		void SetPreviousVelocity(const Vec3f& velocity) noexcept;

		/*
		\brief Getter of the velocity
		\return The velocity of the simulation object (current)
		*/
		const Vec3f& GetVelocity() const noexcept;

		/*
		\brief Getter of the last frame velocity
		\return The velocity of the simulation object (last frame)
		*/
		const Vec3f& GetPreviousVelocity() const noexcept;

		/*
		\brief Set the last frame position for the simulation component
		\param position  position (last frame)
		*/
		void SetPreviousPosition(const Vec3f& position) noexcept;
		/*
		\brief Getter of the last frame position
		\return The position of the simulation object (last frame)
		*/
		const Vec3f& GetPreviousPosition() const noexcept;

		/*
		\brief Getter of the mass
		\return The mass of the simulation object
		*/
		float GetMass() const noexcept;

		/*
		\brief Getter of the inverse mass 
		\return The inverse of the mass of the simulation object
		*/
		float GetInverseMass() const noexcept;


		/*
		\brief Getter of the active flag
		\return True if the simulation component is active, otherwise false
		*/
		bool IsActive() const noexcept;


		/*
		\brief Setter for the active flag
		*/
		void SetActive(bool active) noexcept;


	};

	/*
	\brief SimulationComponent state holds the information of a 
	simulation component and it is used in RK4 integration.
	*/
	struct SimulationComponentState
	{
		Vec3f force;
		Vec3f velocity;
		float mass;
		SimulationComponent* parent{ nullptr };
	};
}


#endif