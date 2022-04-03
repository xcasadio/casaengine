#include "Entities/BaseEntity.h"

#include "Circle2DColliderComponent.h"
#include "Entities/ComponentTypeEnum.h"

namespace CasaEngine
{
	Circle2DColliderComponent::Circle2DColliderComponent(BaseEntity* pEntity_)
		: ColliderComponent(pEntity_, CIRCLE2D_COLLIDER)
	{
		m_pShape = &m_Circle;
	}

	void Circle2DColliderComponent::SetCenter(const Vector3F& position)
	{
		m_Circle.Center(position);
	}

	void Circle2DColliderComponent::SetRadius(float radius)
	{
		m_Circle.Radius(radius);
	}

	void Circle2DColliderComponent::Initialize()
	{
		CreateAndSetRigidBody(1.0f);
	}
}
