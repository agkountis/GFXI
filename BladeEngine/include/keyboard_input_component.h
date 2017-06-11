#ifndef BLADE_KEYBOARD_INPUT_COMPONENT_H_
#define BLADE_KEYBOARD_INPUT_COMPONENT_H_
#include "input_component.h"
#include "virtual_keys.h"
#include <map>
#include "command.h"
#include <memory>

namespace Blade
{
	class KeyboardInputComponent : public InputComponent
	{
	public:

		using KeyboardCommandMap = std::map<Virtual_Key, std::shared_ptr<Command>>;

		explicit KeyboardInputComponent(Entity* parent);

		KeyboardInputComponent(const KeyboardInputComponent& other) = delete;

		KeyboardInputComponent& operator=(const KeyboardInputComponent& other) = delete;

		virtual ~KeyboardInputComponent();

		virtual void Update(const float dt, const long time = 0) noexcept =0;

		virtual void Setup() noexcept = 0;
		
		virtual void Teardown() noexcept = 0;


		bool LoadConfiguration(std::vector<Virtual_Key>& keys, const std::vector<std::shared_ptr<Command>> &commands) noexcept;

		bool LoadConfiguration(const KeyboardCommandMap& map);

		const KeyboardCommandMap& GetKeyboardCommandMap() const noexcept
		{
			return m_KeyboardCommandMap;
		}
	
	protected:
		//#needtorefactor instead of int we're going to use what Chris use to map the manager
		
		/*
		\brief Stores the map that associate the keyboard buttons to commands.
		\details this map will be used by a specified version of this class that will initialize the map to
		use a pre-defined key bindings and control scheme
		*/
		KeyboardCommandMap m_KeyboardCommandMap;
	};
}
#endif // !BLADE_KEYBOARD_INPUT_COMPONENT_H_
