#ifndef BLADE_SYSTEM_H_
#define BLADE_SYSTEM_H_

namespace Blade
{
	/**
	 * \brief An interface that represents a system of the engine.
	 */
	class System
	{
	public:
		/**
		 * \brief Default constructor of a System.
		 */
		System() = default;

		/**
		 * \brief Default destructor of a System.
		 */
		virtual ~System();

		/**
		 * \brief Pure virtual method implemented by the engine's 
		 * systems to perform their initialization.
		 * \return TRUE if initialization is successfull, FALSE otherwise.
		 */
		virtual bool Initialize() noexcept = 0;

		/**
		 * \brief Pure virtual method implemented by the engine's systems to process the
		 * registered components.
		 * \param deltaTime The time elapsed from the previous frame of the application.
		 */
		virtual void Process(float deltaTime) noexcept = 0;
	};
}

#endif //BLADE_SYSTEM_H_
