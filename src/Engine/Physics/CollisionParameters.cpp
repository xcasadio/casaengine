#include  "CollisionParameters.hpp"

namespace CasaEngine
{
	CollisionParameters::CollisionParameters(BaseEntity* entity, Collision* collision)
	{
		CA_ASSERT(entity != nullptr, "CollisionParameters : BaseEntity is null")
		CA_ASSERT(collision != nullptr, "CollisionParameters : Collision is null")

		_entity = entity;
		_collision = collision;
	}

	BaseEntity* CollisionParameters::GetEntity()
	{
		return _entity;
	}

	Collision* CollisionParameters::GetCollision()
	{
		return _collision;
	}
}