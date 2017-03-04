#include "camera_component.h"
#include "engine_context.h"
#include "entity.h"

namespace Blade
{
	CameraComponent::CameraComponent(Entity* parent)
		: Component{ ID_CAMERA_COMPONENT, parent }
	{
		EngineContext::GetCameraSystem()->RegisterComponent(this);
	}

	CameraComponent::CameraComponent(Entity* parent,
	                                 float fov,
	                                 const Viewport& viewport,
	                                 float nearPlane,
	                                 float farPlane)
		: Component{ ID_CAMERA_COMPONENT, parent },
		  m_Fov{ fov },
		  m_Viewport{ viewport },
		  m_ClippingPlanes{ Vec2f{ nearPlane, farPlane } }
	{
		EngineContext::GetCameraSystem()->RegisterComponent(this);
	}

	CameraComponent::CameraComponent(Entity* parent,
	                                 float fov,
	                                 const Viewport& viewport,
	                                 const Vec2f& clippingPlanes)
		: Component{ ID_CAMERA_COMPONENT, parent },
		  m_Fov{ fov },
		  m_Viewport{ viewport },
		  m_ClippingPlanes{ clippingPlanes }
	{
		EngineContext::GetCameraSystem()->RegisterComponent(this);
	}

	CameraComponent::~CameraComponent()
	{
		EngineContext::GetCameraSystem()->UnregisterComponent(GetId());
	}

	float CameraComponent::GetFov() const noexcept
	{
		return m_Fov;
	}

	void CameraComponent::SetFov(float fov) noexcept
	{
		m_Fov = fov;
	}

	const Viewport& CameraComponent::GetViewport() const noexcept
	{
		return m_Viewport;
	}

	void CameraComponent::SetViewport(const Viewport& viewport) noexcept
	{
		m_Viewport = viewport;
	}

	const Vec2f& CameraComponent::GetClippingPlanes() const noexcept
	{
		return m_ClippingPlanes;
	}

	void CameraComponent::SetClippingPlanes(float nearPlane, float farPlane) noexcept
	{
		m_ClippingPlanes.x = nearPlane;
		m_ClippingPlanes.y = farPlane;
	}

	void CameraComponent::SetClippingPlanes(const Vec2f& clippingPlanes) noexcept
	{
		m_ClippingPlanes = clippingPlanes;
	}

	float CameraComponent::GetNearPlane() const noexcept
	{
		return m_ClippingPlanes.x;
	}

	void CameraComponent::SetNearPlane(float nearPlane) noexcept
	{
		m_ClippingPlanes.x = nearPlane;
	}

	float CameraComponent::GetFarPlane() const noexcept
	{
		return m_ClippingPlanes.y;
	}

	void CameraComponent::SetFarPlane(float farPlane) noexcept
	{
		m_ClippingPlanes.y = farPlane;
	}

	const Mat4f& CameraComponent::GetViewMatrix() const noexcept
	{
		return m_ViewMatrix;
	}

	const Mat4f& CameraComponent::GetProjectionMatrix() const noexcept
	{
		return m_ProjectionMatrix;
	}

	void CameraComponent::Setup() noexcept
	{
		Recti rect{ m_Viewport.GetRect() };
		m_ProjectionMatrix = MathUtils::PerspectiveLH(m_Fov, rect.z, rect.w, m_ClippingPlanes.x, m_ClippingPlanes.y);
	}

	void CameraComponent::Update(float dt, long time) noexcept
	{
		m_ViewMatrix = MathUtils::Inverse(GetParent()->GetXform());
	}

	void CameraComponent::Teardown() noexcept
	{
	}
}
