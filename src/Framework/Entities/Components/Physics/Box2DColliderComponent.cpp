#include "Entities/BaseEntity.h"

#include "Box2DColliderComponent.h"
#include "Entities/ComponentTypeEnum.h"

#include "Game/Game.h"
#include "Maths/Rectangle.h"

namespace CasaEngine
{
	Box2DColliderComponent::Box2DColliderComponent(BaseEntity* pEntity_)
		: ColliderComponent(pEntity_, BOX2D_COLLIDER)
	{
		m_pShape = &m_Box;
	}

	void Box2DColliderComponent::Initialize()
	{
		CreateAndSetRigidBody(1.0f);
	}

	void Box2DColliderComponent::Set(float left, float top, float width, float height)
	{
		m_Box.Set(left, top, width, height);
	}

	void Box2DColliderComponent::Write(std::ostream& /*os*/) const
	{

	}

	void Box2DColliderComponent::Read(std::ifstream& /*is*/)
	{

	}
}
