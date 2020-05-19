#ifndef CAMERA2DTARGETDCONTROLLER_H_
#define CAMERA2DTARGETDCONTROLLER_H_

#include "CameraController.h"

namespace CasaEngine
{
	class CA_EXPORT Camera2DTargetedController :
		public ICameraController
	{
	public:
		explicit Camera2DTargetedController(CameraComponent* pCamera);

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void ViewMatrix(Matrix4& viewMatrix_) override;
		void ProjectionMatrix(Matrix4& projectionMatrix_) override;

		void SetTargetedEntity(BaseEntity* pTargetedEntity);
		void SetDeadZoneRatio(Vector2F deadZoneRatio);
		Vector2I GetOffset() const;
		void SetOffset(Vector2I center);
		RectangleI GetLimits() const;
		void SetLimits(RectangleI limits);

	private:
		BaseEntity* m_pTargetedEntity;
		Vector2F m_DeadZoneRatio;
		Vector2I m_Offset;
		RectangleI m_Limits;
	};
}
#endif
