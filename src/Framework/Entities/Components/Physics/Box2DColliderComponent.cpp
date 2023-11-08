#include  "Entities/BaseEntity.hpp"

#include  "Box2DColliderComponent.hpp"
#include  "Entities/ComponentTypeEnum.hpp"

#include  "Game/Game.hpp"
#include  "Maths/Rectangle.hpp"

namespace CasaEngine
{
	Box2DColliderComponent::Box2DColliderComponent(BaseEntity* entity_)
		: ColliderComponent(entity_, BOX2D_COLLIDER)
	{
		_shape = &_box;
	}

	void Box2DColliderComponent::Initialize()
	{
		CreateAndSetRigidBody(1.0f);
	}

	void Box2DColliderComponent::Set(float left, float top, float width, float height)
	{
		_box.Set(left, top, width, height);
	}

	void Box2DColliderComponent::Write(std::ostream& /*os*/) const
	{

	}

	void Box2DColliderComponent::Read(std::ifstream& /*is*/)
	{

	}
}
