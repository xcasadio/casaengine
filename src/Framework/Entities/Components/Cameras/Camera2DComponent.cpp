#include "Entities/BaseEntity.h"

#include "Camera2DComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/ComponentTypeEnum.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"

namespace CasaEngine
{
	Camera2DComponent::Camera2DComponent(BaseEntity* pEntity_)
		: CameraComponent(pEntity_, CAMERA_2D)
	{}

	void Camera2DComponent::Initialize()
	{
	}

	Camera2DComponent::Camera2DComponent(BaseEntity* pEntity_, int type)
		: CameraComponent(pEntity_, type)
	{
	}

	void Camera2DComponent::ComputeProjectionMatrix()
	{
		m_ProjectionMatrix = Matrix4::CreateOrthographicOffCenter(
			m_Viewport.X(),
			m_Viewport.Width() * Game::Instance().GetWindowSize().x,
			m_Viewport.Height() * Game::Instance().GetWindowSize().y,
			m_Viewport.Y(),
			m_Viewport.NearClipPlane(),
			m_Viewport.FarClipPlane());
		//m_ProjectionMatrix = Matrix4::Transpose(m_ProjectionMatrix);
	}

	void Camera2DComponent::ComputeViewMatrix()
	{
		const auto position = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>()->GetPosition();
		m_ViewMatrix = Matrix4::CreateTranslation(position.x, position.y, position.z);
	}
}
