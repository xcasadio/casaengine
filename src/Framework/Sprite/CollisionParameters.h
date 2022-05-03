#pragma once

#include "CA_Export.h"
#include "Entities/BaseEntity.h"
#include "Collision.h"

namespace CasaEngine
{
	class CA_EXPORT CollisionParameters
	{
	public:
		BaseEntity* entity = nullptr;
		Collision* collision = nullptr;
	};

}
