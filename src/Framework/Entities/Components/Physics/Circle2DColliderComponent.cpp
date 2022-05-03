#include "Entities/BaseEntity.h"

#include "Circle2DColliderComponent.h"
#include "Entities/ComponentTypeEnum.h"

namespace CasaEngine
{
	Circle2DColliderComponent::Circle2DColliderComponent(BaseEntity* entity_)
		: ColliderComponent(entity_, CIRCLE2D_COLLIDER)
	{
		_shape = &_circle;
	}

	void Circle2DColliderComponent::SetCenter(const Vector3& position)
	{
		_circle.Center(position);
	}

	void Circle2DColliderComponent::SetRadius(float radius)
	{
		_circle.Radius(radius);
	}

	void Circle2DColliderComponent::Initialize()
	{
		CreateAndSetRigidBody(1.0f);
	}
}
