#pragma once

#include  "Camera3DComponent.hpp"

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
		void SetDeadZoneRatio(Vector2 deadZoneRatio);
		Vector2I GetOffset() const;
		void SetOffset(Vector2I offset);
		Rectangle GetLimits() const;
		void SetLimits(const Rectangle& limits);

	private:
		BaseEntity* m_pTargetedEntity;
		Vector2 m_DeadZoneRatio;
		Vector2I m_Offset;
		Rectangle m_Limits;
	};
}
