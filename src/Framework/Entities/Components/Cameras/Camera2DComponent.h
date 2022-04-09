#pragma once

#include "CA_Export.h"
#include "Entities/Components/CameraComponent.h"

namespace CasaEngine
{
	class CA_EXPORT Camera2DComponent :
		public CameraComponent
	{
	public:
		Camera2DComponent(BaseEntity* pEntity_);
		void Initialize() override;

	protected:
		Camera2DComponent(BaseEntity* pEntity_, int type);

		void ComputeProjectionMatrix() override;
		void ComputeViewMatrix() override;
	};
}
