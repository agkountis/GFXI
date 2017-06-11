#include "..\include\player.h"
#include "engine_context.h"


using namespace Blade;

int Player::m_InstanceCount{ 0 };



Player::Player(const std::string& name, const std::wstring& modelPath, bool local):
	Blade::Entity(name)
{
	
	Load(MODELS_PATH+ modelPath);
	  

	this->SetPosition(Blade::Vec3f{ 1.0f, 5.0f,0.0f });


	if (local)
	{
		Blade::SimulationComponent* simC3{ new Blade::SimulationComponent{ this,1.0f } };
		JoypadNumber jNum;
		switch (m_InstanceCount)
		{
		case 0:
			jNum = JoypadNumber::JOYPAD1;
			break;
		case 1:
			jNum = JoypadNumber::JOYPAD2;
			break;
		case 2:
			jNum = JoypadNumber::JOYPAD3;
			break;
		case 3:
			jNum = JoypadNumber::JOYPAD4;
		   break;
		default:
			jNum = JoypadNumber::JOYPAD1;
			break;


		}


		PlayerJoypadComponent* tjc{ new PlayerJoypadComponent{ this,jNum} };
		tjc->Setup();
	}

	PlayerBehaviour* pb = new PlayerBehaviour(this, local);
	Blade::ColliderComponent* colC3{ new Blade::ColliderComponent{ this,std::make_unique<Blade::BoundingSphere>(1.0f) } };
	colC3->SetListener(pb);
	++m_InstanceCount;
}


Player::~Player()
{


}
