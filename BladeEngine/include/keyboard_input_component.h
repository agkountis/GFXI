#ifndef BLADE_KEYBOARD_INPUT_COMPONENT_H_
#define BLADE_KEYBOARD_INPUT_COMPONENT_H_
#include "input_component.h"
#include "virtual_keys.h"
#include <map>
#include "command.h"
#include <memory>

namespace Blade
{
	/**
	 * \brief An implementation of the InputComponent that handles keyboard input.
	 */
	class KeyboardInputComponent : public InputComponent
	{
	public:

		using KeyboardCommandMap = std::map<VirtualKey, std::shared_ptr<Command>>;

		explicit KeyboardInputComponent(Entity* parent, bool online);

		KeyboardInputComponent(const KeyboardInputComponent& other) = delete;

		KeyboardInputComponent& operator=(const KeyboardInputComponent& other) = delete;

		virtual ~KeyboardInputComponent();

		void Update(const float dt, const long time = 0) noexcept override =0;

		void Setup() noexcept override = 0;

		void Teardown() noexcept override = 0;


		/**
		 * \brief Maps the specified VirtualKeys with the specified Commands.
		 * \param keys A vector of VirtualKeys.
		 * \param commands A vector of Commands.
		 * \return TRUE if successful, FALSE otherwise.
		 */
		bool LoadConfiguration(std::vector<VirtualKey>& keys, const std::vector<std::shared_ptr<Command>> &commands) noexcept;

		/**
		 * \brief Sets the map of VirtualKeys and Commands to the components.
		 * \param map The map of VirtualKeys and Commands.
		 * \return TRUE if successful, FALSE otherwise.
		 */
		bool LoadConfiguration(const KeyboardCommandMap& map);

		/**
		 * \brief Returns the map of VirtualKeys and Commands.
		 * \return The map of VirtualKeys and Commands.
		 */
		const KeyboardCommandMap& GetKeyboardCommandMap() const noexcept
		{
			return m_KeyboardCommandMap;
		}
	
	protected:
		
		/**
		 * \brief Stores the map that associate the keyboard buttons to commands.
		 * \details this map will be used by a specified version of this class that will initialize the map to
		 * use a pre-defined key bindings and control scheme
		 */
		KeyboardCommandMap m_KeyboardCommandMap;
		
	};
}
#endif // !BLADE_KEYBOARD_INPUT_COMPONENT_H_
