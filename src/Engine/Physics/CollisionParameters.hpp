#pragma once

#include "CA_Export.hpp"
#include  "Entities/BaseEntity.hpp"
#include  "Collision.hpp"

namespace CasaEngine
{
	class CA_EXPORT CollisionParameters
	{
	public:
		CollisionParameters(BaseEntity* entity, Collision* collision);

		BaseEntity* GetEntity();
		Collision* GetCollision();

	private:
		BaseEntity* _entity;
		Collision* _collision;
	};
}
