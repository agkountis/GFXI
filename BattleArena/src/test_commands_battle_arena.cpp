#include "test_commands_battle_arena.h"

Blade::JoypadNumber GetJoypadNumberByEntity(Blade::Entity * entity)
{
	using namespace Blade;
	auto  comp = static_cast<JoypadInputComponent*>(entity->GetComponent("co_jpic"));
	return comp->m_JoypadNum;
}
