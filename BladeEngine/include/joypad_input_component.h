#ifndef BLADE_JOYPAD_INPUT_COMPONENT_H_
#define BLADE_JOYPAD_INPUT_COMPOENT_H_
#include "input_component.h"
#include <map>
#include "command.h"
#include <memory>
#include "input_manager.h"
namespace Blade
{
	enum class JOYPAD_ENUM : int
	{
		a,
		b,
		c
	};


	/*
	\brief Joypad abstract class of the engine.
	*/
	class JoypadInputComponent : public InputComponent
	{
		using JoypadCommandMap = std::map<JOYPAD_ENUM, std::shared_ptr<Command>>;


	public:
		JoypadInputComponent(const std::string& type, Entity* parent, Player joypad_number);

		JoypadInputComponent(const JoypadInputComponent&other) = delete;

		JoypadInputComponent& operator= (const JoypadInputComponent& other) = delete;
	
		virtual ~JoypadInputComponent();

		virtual void Update(const float dt, const long time = 0) noexcept = 0;

		virtual void SetUp() noexcept = 0;

		virtual void Teardown() noexcept = 0;

		//#needtorefactor the first vector should not use the integer but the joy pad enum
		bool LoadConfiguration(const std::vector<JOYPAD_ENUM>& control, const std::vector<std::shared_ptr<Command>>& commands) noexcept;

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

	private:
		Player m_Player;
	};
}

#endif
