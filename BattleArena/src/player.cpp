#include "player.h"
#include "engine_context.h"
#include "math_utils.h"
using namespace Blade;

Player::Player(const std::string& name):
	Blade::Entity(name)
{


}


Player::~Player()
{
	//delete m_Dummy;

}

Vec3f Player::GetHeading() noexcept
{

	Quatf q = this->GetOrientation();

	Vec3f output = MathUtils::Normalize(Vec3f(Mat4f(q)*Vec4f(0,0,1,0)));
//	BLADE_TRACE("HEADING VECTOR: " << output.x << ", " << output.y << ", " << output.z);
	return  output;
}
