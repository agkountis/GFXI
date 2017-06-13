#include "..\include\test_behaviour.h"






TestBehaviour::TestBehaviour(Blade::Entity * parent):
	Blade::BehaviourComponent("co_test_behaviour",parent)
{
}

TestBehaviour::~TestBehaviour()
{
}

void TestBehaviour::Update(const float dt, const long time) noexcept
{
	//BLADE_TRACE("UPDATE on test behaviour");


}

void TestBehaviour::Setup() noexcept
{
   
}

void TestBehaviour::Teardown() noexcept
{
}
