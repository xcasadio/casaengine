#ifndef CAMERA2DCOMPONENT_H_
#define CAMERA2DCOMPONENT_H_

#include "CA_Export.h"
#include "Entities/Components/CameraComponent.h"
#include "Transform2DComponent.h"


namespace CasaEngine
{
	class CA_EXPORT Camera2DComponent :
		public CameraComponent
	{
	public:
		Camera2DComponent(BaseEntity* pEntity_);

		void Initialize() override;

	protected:
		void ComputeProjectionMatrix() override;
		void ComputeViewMatrix() override;
	private:
		Transform2DComponent* m_pTransform;
		Vector2F m_Position;
		float m_Zoom;
	};

}

#endif
