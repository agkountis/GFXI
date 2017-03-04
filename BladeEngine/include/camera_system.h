#ifndef BLADE_CAMERA_SYSTEM_H_
#define BLADE_CAMERA_SYSTEM_H_
#include "system.h"
#include <map>
#include "camera_component.h"

namespace Blade
{
	/**
	 * \brief A System responsible to processe and manage the CameraComponents
	 * by swapping the current active camera and providing the current active camera's
	 * matrices.
	 */
	class CameraSystem : public System
	{
	private:
		/**
		 * \brief The registered CameraComponents.
		 */
		std::map<std::string, CameraComponent*> m_CameraComponents;

		/**
		 * \brief The current active CameraComponent.
		 */
		CameraComponent* p_ActiveCamera{ nullptr };

		/**
		* \brief Initializes the CameraSystem.
		* \return TRUE if initialization is successfull, FALSE otherwise.
		*/
		bool Initialize() noexcept override;

		/**
		* \brief Processes the CameraComponents.
		* \param deltaTime The time elapsed from the previous frame of the application.
		*/
		void Process(float deltaTime) noexcept override;

	public:
		/**
		 * \brief Registeres the specified CameraComponent to the CameraSystem.
		 * \param cameraComponent The CameraComponent to be registered to the CameraSytstem for processing.
		 */
		void RegisterComponent(CameraComponent* cameraComponent) noexcept;

		/**
		* \brief Unregisters a CameraComponent from the CameraSystem.
		* \param id The unique id of the CameraComponent to be unregistered.
		*/
		void UnregisterComponent(int id) noexcept;

		/**
		 * \brief Set the camera with the specified name as the active camera.
		 * \param name The name of the camera to be set as active.
		 */
		void SetActiveCamera(const std::string& name) noexcept;

		/**
		 * \brief Provides the active camera's view matrix.
		 * \return The active camera's view matrix.
		 */
		const Mat4f& GetActiveCameraViewMatrix() const noexcept;

		/**
		 * \brief Provides the active camera's projection matrix.
		 * \return The active camera's projection matrix.
		 */
		const Mat4f& GetActiveCameraProjectionMatrtix() const noexcept;

		/**
		 * \brief Provides the active camera's Viewport.
		 * \return The active camera's Viewport.
		 */
		const Viewport& GetActiveCameraViewport() const noexcept;

		/**
		 * \brief Provides the active camera's CameraComponent.
		 * \return The active camera's CameraComponent.
		 */
		CameraComponent* GetActiveCamera() const noexcept;

		/**
		 * \brief Provides the CameraComponent of the camera with the specified name.
		 * \param name The name of the camera to be returned.
		 * \return The CameraComponent of the camera with the specified name.
		 */
		CameraComponent* GetCamera(const std::string &name) noexcept;
	};
}

#endif //BLADE_CAMERA_SYSTEM_H_
