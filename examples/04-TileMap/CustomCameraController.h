#ifndef CUSTOMCAMERACONTROLLER_H_
#define CUSTOMCAMERACONTROLLER_H_

#include "Entities/Components/CameraControllers/CameraController.h"

using namespace CasaEngine;

class CustomCameraController :
	public ICameraController
{
public:
	explicit CustomCameraController(CameraComponent* pCamera);

	void Initialize() override;
	void Update(const GameTime& gameTime_) override;
	void ViewMatrix(Matrix4& viewMatrix_) override;
	void ProjectionMatrix(Matrix4& projectionMatrix_) override;

	void SetTargetedEntity(BaseEntity *pTargetedEntity);
	void SetDeadZoneRatio(Vector2F deadZoneRatio);
	Vector2I GetOffset() const;
	void SetOffset(Vector2I center);
	CRectangleI GetLimits() const;
	void SetLimits(CRectangleI limits);

private:
	BaseEntity* m_pTargetedEntity;
	Vector2F m_DeadZoneRatio;
	Vector2I m_Offset;
	CRectangleI m_Limits;
};

#endif // CUSTOMCAMERACONTROLLER_H_
