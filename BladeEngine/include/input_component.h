#ifndef BLADE_INPUT_COMPONENT_H_
#define BLADE_INPUT_COMPONENT_H_
#include "behaviour_component.h"

namespace Blade
{
	/*
	\brief InputComponent class of the engine. All the input components of the engine 
	derive from this abstractClass.
	*/
	class InputComponent : public BehaviourComponent
	{
	public:
		/*
		\brief Input component constructor.
		\param type The type of the InputComponent as a string
		\param parent The entity the InputComponent will be attached to.
		*/
		InputComponent(const std::string& type, Entity* parent);

		InputComponent(const InputComponent& other) = delete;

		InputComponent& operator=(const InputComponent& other) = delete;

		virtual ~InputComponent();

		/*
		\brief Update the input component
		*/
		virtual void Update(const float dt, const long time = 0) noexcept = 0;

		virtual void SetUp() noexcept = 0;

		virtual void Teardown() noexcept = 0;
			
	};

}

#endif