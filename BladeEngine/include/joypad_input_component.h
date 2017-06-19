#ifndef BLADE_JOYPAD_INPUT_COMPONENT_H_
#define BLADE_JOYPAD_INPUT_COMPONENT_H_
#include "input_component.h"
#include "input_manager.h"
#include <map>
#include "command.h"
#include <memory>
namespace Blade
{
	using JoypadCommandMap = std::map<InputSensor, std::shared_ptr<Command>>;

	/**
	 * \brief Joypad abstract class of the engine.
	 */
	class JoypadInputComponent : public InputComponent
	{
	protected:
		//#needtorefactor instead of int use what the input manager uses as joy pad enum

		/**
		 * \brief Stores the map that associate the joy pad (buttons, triggers and analog sticks) to
		 * a command.
		 * \details this map will be used by a specified version of this class that will initialize the map to
		 * use a pre-defined key bindings and control scheme
		 */
		JoypadCommandMap m_JoypadCommandMap;

	public:
		explicit JoypadInputComponent(Entity* parent, JoypadNumber joypad_number, bool online);

		JoypadInputComponent(const JoypadInputComponent&other) = delete;

		JoypadInputComponent& operator= (const JoypadInputComponent& other) = delete;
	
		virtual ~JoypadInputComponent();

		void Update(const float dt, const long time = 0) noexcept override = 0;

		void Setup() noexcept override = 0;

		void Teardown() noexcept override = 0;

		//#needtorefactor the first vector should not use the integer but the joy pad enum
		/**
		 * \brief Maps the specified InputSensors with the corresponding commands.
		 * \param control A vector of the input sensors.
		 * \param commands A vector of the Commands to be mapped to each sensor.
		 * \return TRUE if successfull, FALSE otherwise.
		 */
		bool LoadConfiguration(const std::vector<InputSensor>& control, const std::vector<std::shared_ptr<Command>>& commands) noexcept;

		/**
		 * \brief 
		 * \param map A map of InputSensors and commands.
		 * \return TRUE if successfull, FALSE otherwise.
		 */
		bool LoadConfiguration(const JoypadCommandMap& map);

		/**
		 * \brief Returns the map of InputSensors and Commands.
		 * \return The map of InputSensors and Commands.
		 */
		const JoypadCommandMap& GetCommandMap() const noexcept
		{
			return m_JoypadCommandMap;
		}

		JoypadNumber m_JoypadNum; 
	};
}

#endif
