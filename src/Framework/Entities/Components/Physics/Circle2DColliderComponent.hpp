#pragma once

#include "CA_Export.hpp"
#include  "ColliderComponent.hpp"
#include  "Maths/Shape/Circle.hpp"

namespace CasaEngine
{
	class CA_EXPORT Circle2DColliderComponent :
		public ColliderComponent
	{
	public:
		Circle2DColliderComponent(BaseEntity* entity_);
		~Circle2DColliderComponent() override = default;
		
		void Initialize() override;

		void SetCenter(const Vector3& position);
		void SetRadius(float radius);

	private:
		Circle _circle;
	};

}
