#pragma once
#include  "Physics/CollisionParameters.hpp"

namespace CasaEngine
{
	class CollisionParametersBetween2Entities
	{
	public:
		CollisionParametersBetween2Entities(CollisionParameters* collisionParameters1, CollisionParameters* collisionParameters2);

		CollisionParameters* CollisionParameters1() const;
		CollisionParameters* CollisionParameters2() const;

	private:
		CollisionParameters* _collisionParameters1;
		CollisionParameters* _collisionParameters2;
	};
}
