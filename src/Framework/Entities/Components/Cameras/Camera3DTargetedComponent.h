#pragma once

#include "Camera3DComponent.h"

namespace CasaEngine
{
	class CA_EXPORT Camera3DTargetedComponent :
		public Camera3DComponent
	{
	public:
		explicit Camera3DTargetedComponent(BaseEntity* entity);
		
		void Update(const GameTime& gameTime_) override;
		void ComputeViewMatrix() override;

		void SetTargetedEntity(BaseEntity* pTargetedEntity);
		void SetDeadZoneRatio(Vector2F deadZoneRatio);
		Vector2I GetOffset() const;
		void SetOffset(Vector2I offset);
		RectangleI GetLimits() const;
		void SetLimits(const RectangleI& limits);

	private:
		BaseEntity* m_pTargetedEntity;
		Vector2F m_DeadZoneRatio;
		Vector2I m_Offset;
		RectangleI m_Limits;
	};
}
