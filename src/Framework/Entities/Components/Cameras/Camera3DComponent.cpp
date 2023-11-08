#include  "Entities/BaseEntity.hpp"

#include  "Camera3DComponent.hpp"
#include  "Maths/Matrix4.hpp"
#include  "Game/Game.hpp"
#include  "StringUtils.hpp"


namespace CasaEngine
{
	Camera3DComponent::Camera3DComponent(BaseEntity* entity, int type)
		: CameraComponent(entity, type),
		m_fFOV(Math::PI_OVER_4)
	{
	}

	void Camera3DComponent::Initialize()
	{
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
