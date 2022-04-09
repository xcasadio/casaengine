#include "Camera2DTargetedComponent.h"

#include "Entities/Components/Transform3DComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"

namespace CasaEngine
{
	Camera2DTargetedComponent::Camera2DTargetedComponent(BaseEntity *entity) :
		Camera2DComponent(entity, CAMERA_2D_TARGETED),
		m_pTargetedEntity(nullptr)
	{
	}

	void Camera2DTargetedComponent::Update(const GameTime& gameTime_)
	{
		if (m_pTargetedEntity != nullptr)
		{
			auto viewport = GetViewport();
			const auto winSize = Game::Instance().GetWindowSize();
			auto* const transform_3d_component = m_pTargetedEntity->GetComponentMgr()->GetComponent<Transform3DComponent>();
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

	void Camera2DTargetedComponent::ComputeViewMatrix()
	{
		m_ViewMatrix = Matrix4::CreateTranslation(-m_Offset.x, -m_Offset.y, 0.0f);
	}

	void Camera2DTargetedComponent::SetTargetedEntity(BaseEntity* pTargetedEntity)
	{
		m_pTargetedEntity = pTargetedEntity;
	}

	void Camera2DTargetedComponent::SetDeadZoneRatio(Vector2F deadZoneRatio)
	{
		m_DeadZoneRatio = deadZoneRatio;
	}

	Vector2I Camera2DTargetedComponent::GetOffset() const
	{
		return m_Offset;
	}

	void Camera2DTargetedComponent::SetOffset(Vector2I offset)
	{
		m_Offset = offset;
	}

	RectangleI Camera2DTargetedComponent::GetLimits() const
	{
		return m_Limits;
	}

	void Camera2DTargetedComponent::SetLimits(RectangleI limits)
	{
		m_Limits = limits;
	}
}
