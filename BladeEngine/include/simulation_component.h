#ifndef BLADE_SIMULATION_COMPONENT_H_
#define BLADE_SIMULATION_COMPONENT_H_
#include "component.h"

namespace Blade
{
	//Forward declaration
	class Entity;

	/*
	\brief SimulationComponent is the component used to perform linear motion
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
		bool m_IsActive{ true };

	public:
		/**
		* \brief Creates new instance of simulation component.
		* \param mass Mass of the physics body (kilograms assumed).
		* \param parent Pointer to parent entity of the component.
		*/
		SimulationComponent(Entity* parent, float mass);

		~SimulationComponent();


		/**
		* \brief Sets acceleration vector of the body represented by this component.
		* \param acceleration Acceleration vector of the body represented by this component
		*/
		void SetAcceleration(const Vec3f& acceleration) noexcept { m_Acceleration = acceleration; }


		/**
		* \brief Return acceleration vector of the body represented by this component.
		* \return Acceleration vector of the body represented by this component.
		*/
		const Vec3f& GetAcceleration() const noexcept { return m_Acceleration; }

		/**
		* \brief Adds a new force to the body.
		* \param force new force to be added.
		*/
		void AddForce(const Vec3f& force) noexcept;

		/**
		* \brief Sets directly the value of the force acting on the body.
		* \param force value of the force acting on the body.
		*/
		void SetForce(const Vec3f& force) noexcept;

		/**
		* \brief Set the value of last frame force accumulator.
		* \param force Value of last frame force accumulator.
		*/
		void SetPreviousForce(const Vec3f& force) noexcept;

		/**
		* \brief Return the value of force that is acting on the body.
		* \return The force accumulator value (current).
		*/
		const Vec3f& GetForce() const noexcept;

		/**
		* \brief Return the value of the last frame force accumulator.
		* \return The force accumulator value (last frame)
		*/
		const Vec3f& GetPreviousForce() const noexcept;

		//#warning check if the reset functionalities also in the system.
		/**
		* \brief Clears force accumulator (current).
		*/
		void ResetForce() noexcept;

		/**
		* \brief Sets new velocity of the body represented by this simulation component.
		* \param velocity New velocity  (current)
		*/
		void SetVelocity(const Vec3f& velocity) noexcept;

		/**
		* \brief Set the last frame velocity for this simulation component.
		* \param velocity New velocity (last frame)
		*/
		void SetPreviousVelocity(const Vec3f& velocity) noexcept;

		/**
		* \brief Retruns velocity of the body represented by this simulation component.
		* \return The velocity of the simulation object (current).
		*/
		const Vec3f& GetVelocity() const noexcept;

		/**
		* \brief Returns the last frame velocity vector.
		* \return The velocity of the body (last frame).
		*/
		const Vec3f& GetPreviousVelocity() const noexcept;

		/**
		* \brief Sets the last frame position for the simulation component.
		* \param position Position (last frame)
		*/
		void SetPreviousPosition(const Vec3f& position) noexcept;
		/*
		* \brief Returns the last frame position.
		* \return The position of the simulation object (last frame).
		*/
		const Vec3f& GetPreviousPosition() const noexcept;

		/**
		* \brief Returns the mass of the body represented by this simulation object.
		* \return The mass of the simulation object.
		*/
		float GetMass() const noexcept;

		/**
		* \brief Returns the inverse of the mass of the body represented by this simulation object.
		* \return The inverse of the mass of the simulation object
		*/
		float GetInverseMass() const noexcept;


		/**
		* \brief Return activity flag.
		* \return True if the simulation component is active, otherwise false
		*/
		bool IsActive() const noexcept;


		/**
		* \brief Setter for the active flag
		*/
		void SetActive(bool active) noexcept;


	};

	/*
	* \brief SimulationComponentState holds the information about
	* simulation component. It is used by RK4 integrator.
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