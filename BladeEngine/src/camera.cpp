#include "camera.h"
namespace Blade
{
	Camera::Camera(const std::string& name, const CameraDesc& cameraDescription)
		: Entity{ name }
	{
		m_CameraComponent = new CameraComponent{ this,
			cameraDescription.fov,
			cameraDescription.viewport,
			cameraDescription.nearPlane,
			cameraDescription.farPlane };

		m_CameraComponent->UsePerspectiveProjection();

	}

	void Camera::Update(float dt, long time /*= 0*/) noexcept
	{
		Entity::Update(dt);
		m_CameraComponent->SetViewMatrix(MathUtils::Inverse(GetXform()));
	}

}
