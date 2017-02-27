#ifndef BLADE_CAMERA_COMPONENT_H_
#define BLADE_CAMERA_COMPONENT_H_
#include "component.h"
#include "viewport.h"

namespace Blade
{
	class CameraComponent : public Component
	{
	private:
		float m_Fov{ 0.0f };
		Viewport m_Viewport;

		Vec2f m_ClippingPlanes;

		Mat4f m_ViewMatrix;
		Mat4f m_ProjectionMatrix;

	public:
		explicit CameraComponent(Entity* parent);

		~CameraComponent();

		float GetFov() const noexcept;

		void SetFov(float fov) noexcept;

		const Viewport& GetViewport() const noexcept;

		void SetViewport(const Viewport& viewport) noexcept;

		const Vec2f& GetClippingPlanes() const noexcept;

		void SetClippingPlanes(float nearPlane, float farPlane) noexcept;

		void SetClippingPlanes(const Vec2f& clippingPlanes) noexcept;

		float GetNearPlane() const noexcept;

		void SetNearPlane(float nearPlane) noexcept;

		float GetFarPlane() const noexcept;

		void SetFarPlane(float farPlane) noexcept;

		const Mat4f& GetViewMatrix() const noexcept;

		const Mat4f& GetProjectionMatrix() const noexcept;

		void Setup() noexcept override;

		void Update(float dt, long time) noexcept override;
		
		void Teardown() noexcept override;
	};
}

#endif //BLADE_CAMERA_COMPONENT_H_
