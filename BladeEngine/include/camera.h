#ifndef BLADE_CAMERA_H_
#define BLADE_CAMERA_H_
#include "entity.h"
#include "camera_component.h"

namespace Blade
{
	class Entity;

	/**
	* \brief CameraDesc structure describes the camera.
	*/
	struct CameraDesc
	{
		Viewport viewport;
		float nearPlane;
		float farPlane;
		float fov;
	};

	/**
	* \brief Camera class encapsulates model, view and projection matrices. 
	* Camera object provides a behaviour of real life camera. It can be moved around the scene.
	*/
	class Camera : public Entity                                                           
	{
	private:
		CameraComponent* m_CameraComponent{ nullptr };

	public:
		/**
		* \brief Creates new instance of the camera object.
		* \param name Name of the camera to be created.
		* \param cameraDescription Description structure of the camera.
		*/
		Camera(const std::string& name, const CameraDesc& cameraDescription);


		void Update(float dt, long time = 0) noexcept override;
	};
}

#endif //BLADE_CAMERA_H_
