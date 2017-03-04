#include "camera_system.h"
#include "entity.h"
#include <iostream>

namespace Blade
{
	void CameraSystem::RegisterComponent(CameraComponent* cameraComponent) noexcept
	{
		m_CameraComponents[cameraComponent->GetParent()->GetName()] = cameraComponent;
	}

	void CameraSystem::UnregisterComponent(int id) noexcept
	{
		auto it{ m_CameraComponents.begin() };

		while (it != m_CameraComponents.end())
		{
			auto entry{ *it };
			if (entry.second->GetId() == id)
			{
				it = m_CameraComponents.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void CameraSystem::SetActiveCamera(const std::string& name) noexcept
	{
		CameraComponent* camera{ m_CameraComponents[name] };

		if (camera)
		{
			p_ActiveCamera = camera;
		}
		else
		{
			std::cerr << "Cannot locate a camera with the specified name!" << std::endl;
		}
	}

	const Mat4f& CameraSystem::GetActiveCameraViewMatrix() const noexcept
	{
		return p_ActiveCamera->GetViewMatrix();
	}

	const Mat4f& CameraSystem::GetActiveCameraProjectionMatrtix() const noexcept
	{
		return p_ActiveCamera->GetProjectionMatrix();
	}

	const Viewport& CameraSystem::GetActiveCameraViewport() const noexcept
	{
		return p_ActiveCamera->GetViewport();
	}

	CameraComponent* CameraSystem::GetActiveCamera() const noexcept
	{
		return p_ActiveCamera;
	}

	CameraComponent* CameraSystem::GetCamera(const std::string& name) noexcept
	{
		return m_CameraComponents[name];
	}

	bool CameraSystem::Initialize() noexcept
	{
		return true;
	}

	void CameraSystem::Process(float deltaTime) noexcept
	{
	}
}
