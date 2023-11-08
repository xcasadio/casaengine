#pragma once

#include "CA_Export.hpp"
#include  "Entities/Components/CameraComponent.hpp"

namespace CasaEngine
{
	class CA_EXPORT Camera2DComponent :
		public CameraComponent
	{
	public:
		Camera2DComponent(BaseEntity* entity);
		void Initialize() override;

	protected:
		Camera2DComponent(BaseEntity* entity, int type);

		void ComputeProjectionMatrix() override;
		void ComputeViewMatrix() override;
	};
}
