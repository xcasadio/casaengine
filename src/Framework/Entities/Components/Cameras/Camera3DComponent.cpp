#include "Entities/BaseEntity.h"

#include "Camera3DComponent.h"
#include "Maths/Matrix4.h"
#include "Game/Game.h"
#include "StringUtils.h"


namespace CasaEngine
{
	Camera3DComponent::Camera3DComponent(BaseEntity* pEntity_, int type)
		: CameraComponent(pEntity_, type),
		m_fFOV(MATH_PI_DIV_4)
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
