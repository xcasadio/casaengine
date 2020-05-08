#include "CustomCameraController.h"

#include "Entities/Components/Transform2DComponent.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"

using namespace CasaEngine;

CustomCameraController::CustomCameraController(CameraComponent* pCamera):
	ICameraController(pCamera),
	m_pTargetedEntity(nullptr)
{
}

void CustomCameraController::Initialize()
{
	
}

void CustomCameraController::Update(const GameTime& gameTime_)
{
	if (m_pTargetedEntity != nullptr)
	{
		auto viewport = Camera()->GetViewport();
		const auto winSize = Game::Instance()->GetWindow()->getSize();
		const auto transform_3d_component = m_pTargetedEntity->GetComponentMgr()->GetComponent<Transform3DComponent>();
		CA_ASSERT(transform_3d_component != nullptr, "cameracomponent : the target need to have a Transform3DComponent");
		const auto targetPosition = transform_3d_component->GetPosition();

		const CRectangleF deadZone(m_Offset.x + (float)winSize.x * (1.0f - m_DeadZoneRatio.x) / 2.0f,
			m_Offset.y + (float)winSize.y * (1.0f - m_DeadZoneRatio.y) / 2.0f,
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

void CustomCameraController::ViewMatrix(Matrix4& viewMatrix_)
{
	const auto winSize = Game::Instance()->GetWindow()->getSize();
	const auto viewport = Camera()->GetViewport();
	
	if (m_pTargetedEntity != nullptr)
	{
		auto* const transform_3d = m_pTargetedEntity->GetComponentMgr()->GetComponent<Transform3DComponent>();
		auto position = transform_3d->GetPosition();
		viewMatrix_.CreateTranslation(-m_Offset.x, -m_Offset.y, 0.0f);
		//viewMatrix_.Identity();
	}
}

void CustomCameraController::ProjectionMatrix(Matrix4& projectionMatrix_)
{
	auto& viewport = this->Camera()->GetViewport();
	
	projectionMatrix_.OrthoOffCenter(
		static_cast<float>(viewport.X()),
		static_cast<float>(viewport.Y()),
		static_cast<float>(viewport.Width() * Game::Instance()->GetWindow()->getSize().x),
		static_cast<float>(viewport.Height() * Game::Instance()->GetWindow()->getSize().y),
		viewport.NearClipPlane(), viewport.FarClipPlane());
	
	projectionMatrix_ = projectionMatrix_.Transpose(); // TODO check the computation, why need transpose
}

void CustomCameraController::SetTargetedEntity(BaseEntity *pTargetedEntity)
{
	m_pTargetedEntity = pTargetedEntity;
}

void CustomCameraController::SetDeadZoneRatio(Vector2F deadZoneRatio)
{
	m_DeadZoneRatio = deadZoneRatio;
}

Vector2I CustomCameraController::GetOffset() const
{
	return m_Offset;
}

inline void CustomCameraController::SetOffset(Vector2I offset)
{
	m_Offset = offset;
}

CRectangleI CustomCameraController::GetLimits() const
{
	return m_Limits;
}

void CustomCameraController::SetLimits(CRectangleI limits)
{
	m_Limits = limits;
}
