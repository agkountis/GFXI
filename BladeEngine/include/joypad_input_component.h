#ifndef BLADE_JOYPAD_INPUT_COMPONENT_H_
#define BLADE_JOYPAD_INPUT_COMPONENT_H_
#include "input_component.h"
#include "input_manager.h"
#include <map>
#include "command.h"
#include <memory>
namespace Blade
{
	/*
	\brief Joypad abstract class of the engine.
	*/
	class JoypadInputComponent : public InputComponent
	{
		
		using JoypadCommandMap = std::map<InputSensor, std::shared_ptr<Command>>;

	public:
		explicit JoypadInputComponent(Entity* parent, JoypadNumber joypad_number);

		JoypadInputComponent(const JoypadInputComponent&other) = delete;

		JoypadInputComponent& operator= (const JoypadInputComponent& other) = delete;
	
		virtual ~JoypadInputComponent();

		virtual void Update(const float dt, const long time = 0) noexcept = 0;

		virtual void Setup() noexcept = 0;

		virtual void Teardown() noexcept = 0;

		//#needtorefactor the first vector should not use the integer but the joy pad enum
		bool LoadConfiguration(const std::vector<InputSensor>& control, const std::vector<std::shared_ptr<Command>>& commands) noexcept;

		bool LoadConfiguration(const JoypadCommandMap& map);

		const JoypadCommandMap& GetCommandMap() const noexcept
		{
			return m_JoypadCommandMap;
		}
	
	protected:
		//#needtorefactor instead of int use what the input manager uses as joy pad enum

		/*
		\brief Stores the map that associate the joy pad (buttons, triggers and analog sticks) to 
		a command.
		\details this map will be used by a specified version of this class that will initialize the map to 
		use a pre-defined key bindings and control scheme
		*/
		JoypadCommandMap m_JoypadCommandMap;
	public:
		JoypadNumber m_JoypadNum; 
	};
}

#endif
