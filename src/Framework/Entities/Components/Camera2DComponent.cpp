#include "Entities/BaseEntity.h"

#include "Camera2DComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"

#include "Transform2DComponent.h"


namespace CasaEngine
{
	/**
	 *
	 */
	Camera2DComponent::Camera2DComponent(BaseEntity* pEntity_)
		: CameraComponent(pEntity_, CAMERA_2D),
		m_Zoom(1.0f)
	{}

	/**
	 *
	 */
	Camera2DComponent::~Camera2DComponent()
	{
	}

	/**
	 *
	 */
	void Camera2DComponent::Initialize()
	{
	}

	/**
	 *
	 */
	void Camera2DComponent::ComputeProjectionMatrix()
	{
		m_ProjectionMatrix.OrthoOffCenter(
			static_cast<float>(m_Viewport.X()),
			static_cast<float>(m_Viewport.Y()),
			static_cast<float>(m_Viewport.Width() * Game::Instance().GetWindowSize().x),
			static_cast<float>(m_Viewport.Height() * Game::Instance().GetWindowSize().y),
			m_Viewport.NearClipPlane(),
			m_Viewport.FarClipPlane());
		m_ProjectionMatrix = m_ProjectionMatrix.Transpose();
	}

	void Camera2DComponent::ComputeViewMatrix()
	{
		m_ViewMatrix.CreateTranslation(0.0f, 0.0f, 0.0f);
	}
}
