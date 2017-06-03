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

		m_CameraComponent->Setup();
	}
}
