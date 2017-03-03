#ifndef BLADE_CAMERA_COMPONENT_H_
#define BLADE_CAMERA_COMPONENT_H_
#include "component.h"
#include "viewport.h"

namespace Blade
{
	/**
	 * \brief Represents a CameraComponent. This component contains
	 * all the information needed for the view and projection transformations.
	 * Managed by the CameraSystem.
	 */
	class CameraComponent : public Component
	{
	private:
		/**
		 * \brief The field of view.
		 */
		float m_Fov{ 0.0f };
		
		/**
		 * \brief The viewport of the camera.
		 */
		Viewport m_Viewport;

		/**
		 * \brief The clipping planes for the projection.
		 * \details x - The near clipping plane.
		 * \details y - The far clipping plane.
		 */
		Vec2f m_ClippingPlanes;

		/**
		 * \brief The view matrix.
		 */
		Mat4f m_ViewMatrix;

		/**
		 * \brief The projection matrix.
		 */
		Mat4f m_ProjectionMatrix;

		void Teardown() noexcept override;

		//TODO: Later on update matrices only when it's needed. (Dirty bit)

	public:
		/**
		 * \brief CameraComponent's constructor.
		 * \details Registers the component to the CameraSystem.
		 * \param parent The entity the CameraComponent will be attached to.
		 */
		explicit CameraComponent(Entity* parent);

		/**
		 * \overload
		 * \param parent The entity the CameraComponent will be attached to.
		 * \param fov The field of view.
		 * \param viewport The viewport of the camera.
		 * \param nearPlane The near clipping plane.
		 * \param farPlane The far clipping plane.
		 */
		CameraComponent(Entity* parent, float fov, const Viewport& viewport, float nearPlane, float farPlane);

		/**
		 * \overload
		 * \param parent The entity the CameraComponent will be attached to.
		 * \param fov The field of view.
		 * \param viewport The viewport of the camera.
		 * \param clippingPlanes The clipping planes for the projection.
		 * \details clippingPlanes.x - The near clipping plane.
		 * \details clippingPlanes.y - The far clipping plane.
		 */
		CameraComponent(Entity* parent, float fov, const Viewport& viewport, const Vec2f& clippingPlanes);

		/**
		 * \brief CameraComponent's destructor.
		 * \details Unregisters the component from the CameraSystem.
		 */
		~CameraComponent();

		/**
		 * \brief Provides the field of view.
		 * \return The field of view.
		 */
		float GetFov() const noexcept;

		/**
		 * \brief Sets the field of view.
		 * \param fov The field of view.
		 */
		void SetFov(float fov) noexcept;

		/**
		 * \brief Provides the Viewport
		 * \return The Viewport.
		 */
		const Viewport& GetViewport() const noexcept;

		/**
		 * \brief Sets the Viewport.
		 * \param viewport The Viewport.
		 */
		void SetViewport(const Viewport& viewport) noexcept;

		/**
		 * \brief Provides the clipping planes as a Vec2f.
		 * \details x - The near clipping plane.
		 * \details y - The far clipping plane.
		 * \return The clipping planes as a Vec2f.
		 */
		const Vec2f& GetClippingPlanes() const noexcept;

		/**
		 * \brief Sets the near and the far clipping planes.
		 * \param nearPlane The near clipping plane.
		 * \param farPlane The far clipping plane.
		 */
		void SetClippingPlanes(float nearPlane, float farPlane) noexcept;

		/**
		 * \overload void SetClippingPlanes(const Vec2f& clippingPlanes) noexcept
		 * \details x - The near clipping plane.
		 * \details y - The far clipping plane.
		 * \param clippingPlanes The clipping planes as a Vec2f.
		 */
		void SetClippingPlanes(const Vec2f& clippingPlanes) noexcept;

		/**
		 * \brief Provides the near clipping plane.
		 * \return The near clipping plane.
		 */
		float GetNearPlane() const noexcept;

		/**
		 * \brief Sets the near clipping plane.
		 * \param nearPlane The near clipping plane.
		 */
		void SetNearPlane(float nearPlane) noexcept;

		/**
		 * \brief Provides the far clipping plane.
		 * \return The far clipping plane.
		 */
		float GetFarPlane() const noexcept;

		/**
		 * \brief Sets the far clipping plane.
		 * \param farPlane The far clipping plane.
		 */
		void SetFarPlane(float farPlane) noexcept;

		/**
		 * \brief Provides the view matrix.
		 * \return The view matrix.
		 */
		const Mat4f& GetViewMatrix() const noexcept;

		/**
		 * \brief Provides the projection matrix.
		 * \return The projection matrix.
		 */
		const Mat4f& GetProjectionMatrix() const noexcept;

		/**
		 * \brief Sets up the CameraComponent.
		 * \details Calculates and caches the projection matrix.
		 */
		void Setup() noexcept override;

		/**
		 * \brief Updates the CameraComponent
		 * \details Calculates the view matrix.
		 * \param dt The time elapsed from the previous frame of the Application.
		 * \param time The elapsed time since the start of the Application.
		 */
		void Update(float dt, long time) noexcept override;
	};
}

#endif //BLADE_CAMERA_COMPONENT_H_
