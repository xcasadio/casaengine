#pragma once

#include <string>
#include <vector>
#include "CA_Export.hpp"
#include  "Entities/BaseEntity.hpp"
#include  "Maths/Vector3.hpp"
#include  "Physics/PhysicsObjectContainer.hpp"

namespace CasaEngine
{
	class CA_EXPORT SpritePhysicsHelper
	{
	public:
		static std::vector<ICollisionObjectContainer*> CreateCollisionsFromSprite(std::string spriteId, BaseEntity* entity);
		static void AddCollisionFromSprite(ICollisionObjectContainer* collisionObject, const SpriteData* sprite_data, Vector3 translation);
		static void AddCollisionsFromSprite(Vector3 translation, const std::string& spriteId, const std::vector<ICollisionObjectContainer*>& collisionObjects);
	};
}