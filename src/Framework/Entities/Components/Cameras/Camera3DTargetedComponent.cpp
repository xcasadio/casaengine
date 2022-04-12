#include "Camera3DTargetedComponent.h"

#include "Camera3DComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Entities/Components/Transform2DComponent.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"

namespace CasaEngine
{
	Camera3DTargetedComponent::Camera3DTargetedComponent(BaseEntity* entity) :
		Camera3DComponent(entity, CAMERA_3D_TARGETED),
		m_pTargetedEntity(nullptr)
	{
	}

	void Camera3DTargetedComponent::Update(const GameTime& gameTime_)
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

			if (deadZone.Intersects(Vector2(targetPosition.x, targetPosition.y)) == INT_OUT)
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

	void Camera3DTargetedComponent::ComputeViewMatrix()
	{
		m_ViewMatrix.CreateFromDirection(Vector3::UnitZ(), Vector3::UnitX(), -Vector3::UnitY());
		
		/*const float d_yfov_tan = 0.267949192431123f;
		auto& viewport = this->Camera()->GetViewport();
		const float w = static_cast<float>(viewport.Width() * Game::Instance().GetWindowSize().x);
		const float h = static_cast<float>(viewport.Height() * Game::Instance().GetWindowSize().y);
		const float aspect = w / h;
		const float midx = w * 0.5f;
		const float midy = h * 0.5f;
		const float z = midx / (aspect * d_yfov_tan);*/

		auto fov = FOV();
		fov = ToDegree(fov);
		const float z = (Game::Instance().GetWindowSize().x / 2.0f) / std::tan(fov / 2.0f);		
		//viewMatrix_.Translation(-m_Offset.x, -m_Offset.y, z);

		m_ViewMatrix.Identity();
		Vector3 pos(-m_Offset.x, -m_Offset.y, z);
		Vector3 target(-m_Offset.x, -m_Offset.y, 0.0f);
		Vector3 up = -Vector3::UnitY();
		m_ViewMatrix = Matrix4::CreateLookAt(pos, target, up);
	}

	void Camera3DTargetedComponent::SetTargetedEntity(BaseEntity* pTargetedEntity)
	{
		m_pTargetedEntity = pTargetedEntity;
	}

	void Camera3DTargetedComponent::SetDeadZoneRatio(Vector2 deadZoneRatio)
	{
		m_DeadZoneRatio = deadZoneRatio;
	}

	Vector2I Camera3DTargetedComponent::GetOffset() const
	{
		return m_Offset;
	}

	inline void Camera3DTargetedComponent::SetOffset(Vector2I offset)
	{
		m_Offset = offset;
	}

	RectangleI Camera3DTargetedComponent::GetLimits() const
	{
		return m_Limits;
	}

	void Camera3DTargetedComponent::SetLimits(const RectangleI& limits)
	{
		m_Limits = limits;
	}
}
