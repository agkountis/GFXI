#ifndef BLADE_INPUT_STATE_H_
#define BLADE_INPUT_STATE_H_


namespace Blade
{
	/**
	* \brief InputState describes the current state of a device.
	* \details Only joy pad support for the moment. A function to compare two state has to be provided
	*/
	struct InputState
	{
		InputState();
		~InputState();
		InputState(const InputState& src) noexcept = default;
		InputState& operator=(const InputState& rhs)noexcept = default;
		InputState(InputState&& src) noexcept = default;
		InputState& operator=(InputState&& rhs) noexcept = default;

		//Implement a state comparison or something like that here (...)
		
	};

}

#endif
