#pragma once
#include "Physics/CollisionParameters.h"

namespace CasaEngine
{
	class CollisionParametersBetween2Entities
	{
	public:
		CollisionParametersBetween2Entities(CollisionParameters* collisionParameters1, CollisionParameters* collisionParameters2);

	private:
		CollisionParameters* mCollisionParameters1;
		CollisionParameters* mCollisionParameters2;
	};
}
