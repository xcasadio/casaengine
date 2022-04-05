#include "Entities/BaseEntity.h"

#include "Camera3DComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"
#include "StringUtils.h"


namespace CasaEngine
{
	Camera3DComponent::Camera3DComponent(BaseEntity* pEntity_)
		: CameraComponent(pEntity_, CAMERA_3D),
		m_Target(Vector3F::Zero()),
		m_Position(Vector3F(0.0f, 10.0f, -10.0f)),
		m_fFOV(MATH_PI_DIV_4)
	{
	}

	void Camera3DComponent::Initialize()
	{
	}

	Vector3F Camera3DComponent::Position() const
	{
		return m_Position;
	}

	void Camera3DComponent::Position(Vector3F val)
	{
		m_Position = val;
		m_needToComputeViewMatrix = true;
	}

	Vector3F Camera3DComponent::Target() const
	{
		return m_Target;
	}

	void Camera3DComponent::Target(Vector3F val)
	{
		m_Target = val;
		m_needToComputeViewMatrix = true;
	}

	float Camera3DComponent::FOV() const
	{
		return m_fFOV;
	}

	void Camera3DComponent::FOV(float val)
	{
		m_fFOV = val;
		m_needToComputeProjectionMatrix = true;
	}

	float Camera3DComponent::FarClipPlane() const
	{
		return m_Viewport.FarClipPlane();
	}

	void Camera3DComponent::FarClipPlane(float val)
	{
		m_Viewport.FarClipPlane(val);
		m_needToComputeProjectionMatrix = true;
	}

	float Camera3DComponent::NearClipPlane() const
	{
		return m_Viewport.NearClipPlane();
	}

	void Camera3DComponent::NearClipPlane(float val)
	{
		m_Viewport.NearClipPlane(val);
		m_needToComputeProjectionMatrix = true;
	}

	void Camera3DComponent::ComputeViewMatrix()
	{
		m_needToComputeViewMatrix = false;
		m_ViewMatrix = Matrix4::CreateLookAt(m_Position, m_Target, Vector3F::Up());
	}

	void Camera3DComponent::ComputeProjectionMatrix()
	{
		m_needToComputeProjectionMatrix = false;
		float ratio = m_Viewport.Width() * Game::Instance().GetWindowSize().x /
			(m_Viewport.Height() * Game::Instance().GetWindowSize().y);

		m_ProjectionMatrix = Matrix4::CreatePerspectiveFieldOfView(
			m_fFOV,
			ratio,
			m_Viewport.NearClipPlane(),
			m_Viewport.FarClipPlane());
	}

	void Camera3DComponent::Write(std::ostream& /*os*/) const
	{

	}

	void Camera3DComponent::Read(std::ifstream& /*is*/)
	{
	}
}
