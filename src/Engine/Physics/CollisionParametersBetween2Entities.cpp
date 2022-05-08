#include "CollisionParametersBetween2Entities.h"

namespace CasaEngine
{
	CollisionParametersBetween2Entities::CollisionParametersBetween2Entities(CollisionParameters* collisionParameters1, CollisionParameters* collisionParameters2) :
		_collisionParameters1(collisionParameters1),
		_collisionParameters2(collisionParameters2)
	{

	}

	CasaEngine::CollisionParameters* CollisionParametersBetween2Entities::CollisionParameters1() const
	{
		return _collisionParameters1;
	}

	CasaEngine::CollisionParameters* CollisionParametersBetween2Entities::CollisionParameters2() const
	{
		return _collisionParameters2;
	}

}
