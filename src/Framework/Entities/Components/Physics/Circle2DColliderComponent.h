#pragma once

#include "CA_Export.h"
#include "ColliderComponent.h"
#include "Maths/Shape/Circle.h"

namespace CasaEngine
{
	class CA_EXPORT Circle2DColliderComponent :
		public ColliderComponent
	{
	public:
		Circle2DColliderComponent(BaseEntity* pEntity_);
		~Circle2DColliderComponent() override = default;
		
		void Initialize() override;

		void SetCenter(const Vector3& position);
		void SetRadius(float radius);

	private:
		Circle m_Circle;
	};

}
