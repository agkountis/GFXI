#ifndef BLADE_CAMERA_SYSTEM_H_
#define BLADE_CAMERA_SYSTEM_H_
#include "system.h"
#include <map>
#include "camera_component.h"

namespace Blade
{
	class CameraSystem : public System
	{
	private:
		std::map<std::string, CameraComponent*> m_CameraComponents;

		CameraComponent* p_ActiveCamera{ nullptr };

	public:
		void RegisterComponent(CameraComponent* cameraComponent) noexcept;

		void UnregisterComponent(int id) noexcept;

		void SetActiveCamera(const std::string& name) noexcept;

		const Mat4f& GetActiveCameraViewMatrix() const noexcept;

		const Mat4f& GetActiveCameraProjectionMatrtix() const noexcept;

		const Viewport& GetActiveCameraViewport() const noexcept;

		bool Initialize() noexcept override;
	
		void Process(float deltaTime) noexcept override;
	};
}

#endif //BLADE_CAMERA_SYSTEM_H_
