#pragma once

#include "CA_Export.h"
#include "Entities/BaseEntity.h"
#include "Collision.h"

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
