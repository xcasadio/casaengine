#include  "Entities/BaseEntity.hpp"

#include  "Camera2DComponent.hpp"
#include  "Maths/Matrix4.hpp"
#include  "Entities/ComponentTypeEnum.hpp"
#include  "Game/Game.hpp"

namespace CasaEngine
{
	Camera2DComponent::Camera2DComponent(BaseEntity* entity)
		: CameraComponent(entity, CAMERA_2D)
	{}

	void Camera2DComponent::Initialize()
	{
	}

	Camera2DComponent::Camera2DComponent(BaseEntity* entity, int type)
		: CameraComponent(entity, type)
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
		auto position = GetEntity()->GetCoordinates().GetPosition();
		m_ViewMatrix = Matrix4::CreateTranslation(position.x, position.y, position.z);
	}
}
