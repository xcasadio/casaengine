#include "Camera2DTargetedController.h"

#include "Entities/Components/Transform2DComponent.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"

namespace CasaEngine
{
	Camera2DTargetedController::Camera2DTargetedController(CameraComponent* pCamera) :
		ICameraController(pCamera),
		m_pTargetedEntity(nullptr)
	{
	}

	void Camera2DTargetedController::Initialize()
	{

	}

	void Camera2DTargetedController::Update(const GameTime& gameTime_)
	{
		if (m_pTargetedEntity != nullptr)
		{
			auto viewport = Camera()->GetViewport();
			const auto winSize = Game::Instance().GetWindowSize();
			const auto transform_3d_component = m_pTargetedEntity->GetComponentMgr()->GetComponent<Transform3DComponent>();
			CA_ASSERT(transform_3d_component != nullptr, "cameracomponent : the target need to have a Transform3DComponent");
			const auto targetPosition = transform_3d_component->GetPosition();

			const RectangleF deadZone(m_Offset.x + static_cast<float>(winSize.x) * (1.0f - m_DeadZoneRatio.x) / 2.0f,
				m_Offset.y + static_cast<float>(winSize.y) * (1.0f - m_DeadZoneRatio.y) / 2.0f,
				winSize.x * m_DeadZoneRatio.x,
				winSize.y * m_DeadZoneRatio.y);

			if (deadZone.Intersects(Vector2F(targetPosition.x, targetPosition.y)) == INT_OUT)
			{
				if (targetPosition.x < deadZone.Left())
				{
					m_Offset.x -= deadZone.Left() - targetPosition.x;
				}
				else if (targetPosition.x > deadZone.Right())
				{
					m_Offset.x += targetPosition.x - deadZone.Right();
				}

				if (targetPosition.y < deadZone.Top())
				{
					m_Offset.y -= deadZone.Top() - targetPosition.y;
				}
				else if (targetPosition.y > deadZone.Bottom())
				{
					m_Offset.y += targetPosition.y - deadZone.Bottom();
				}

				//limits
				if (m_Offset.x > m_Limits.Right() - static_cast<int>(winSize.x))
				{
					m_Offset.x = m_Limits.Right() - static_cast<int>(winSize.x);
				}

				if (m_Offset.x < m_Limits.Left())
				{
					m_Offset.x = m_Limits.Left();
				}

				if (m_Offset.y > m_Limits.Bottom() - static_cast<int>(winSize.y))
				{
					m_Offset.y = m_Limits.Bottom() - static_cast<int>(winSize.y);
				}

				if (m_Offset.y < m_Limits.Top())
				{
					m_Offset.y = m_Limits.Top();
				}
			}
		}
	}

	void Camera2DTargetedController::ViewMatrix(Matrix4& viewMatrix_)
	{
		viewMatrix_.CreateTranslation(-m_Offset.x, -m_Offset.y, 0.0f);
	}

	void Camera2DTargetedController::ProjectionMatrix(Matrix4& projectionMatrix_)
	{
		auto& viewport = this->Camera()->GetViewport();

		projectionMatrix_.OrthoOffCenter(
			static_cast<float>(viewport.X()),
			static_cast<float>(viewport.Y()),
			static_cast<float>(viewport.Width() * Game::Instance().GetWindowSize().x),
			static_cast<float>(viewport.Height() * Game::Instance().GetWindowSize().y),
			viewport.NearClipPlane(), viewport.FarClipPlane());

		//projectionMatrix_ = projectionMatrix_.Transpose(); // TODO check the computation, why need transpose
	}

	void Camera2DTargetedController::SetTargetedEntity(BaseEntity* pTargetedEntity)
	{
		m_pTargetedEntity = pTargetedEntity;
	}

	void Camera2DTargetedController::SetDeadZoneRatio(Vector2F deadZoneRatio)
	{
		m_DeadZoneRatio = deadZoneRatio;
	}

	Vector2I Camera2DTargetedController::GetOffset() const
	{
		return m_Offset;
	}

	inline void Camera2DTargetedController::SetOffset(Vector2I offset)
	{
		m_Offset = offset;
	}

	RectangleI Camera2DTargetedController::GetLimits() const
	{
		return m_Limits;
	}

	void Camera2DTargetedController::SetLimits(RectangleI limits)
	{
		m_Limits = limits;
	}
}
