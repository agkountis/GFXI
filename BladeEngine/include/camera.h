#ifndef BLADE_CAMERA_H_
#define BLADE_CAMERA_H_
#include "entity.h"
#include "camera_component.h"

namespace Blade
{
	class Entity;

	struct CameraDesc
	{
		Viewport viewport;
		float nearPlane;
		float farPlane;
		float fov;
	};

	class Camera : public Entity
	{
	private:
		CameraComponent* m_CameraComponent{ nullptr };

	public:
		Camera(const std::string& name, const CameraDesc& cameraDescription);
	};
}

#endif //BLADE_CAMERA_H_
