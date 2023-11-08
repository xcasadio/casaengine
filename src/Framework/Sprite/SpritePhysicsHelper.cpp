#include  "Base.hpp"
#include  "SpritePhysicsHelper.hpp"

#include <BulletCollision/CollisionShapes/btBoxShape.h>

#include  "Physics/CollisionParameters.hpp"
#include  "Game/Game.hpp"
#include  "Physics/Bullet/BulletObjectsContainer.hpp"
#include  "Physics/Bullet/BulletPhysicsWorld.hpp"

namespace CasaEngine
{
	std::vector<ICollisionObjectContainer*> SpritePhysicsHelper::CreateCollisionsFromSprite(std::string spriteId, BaseEntity* entity)
	{
		std::vector<ICollisionObjectContainer*> collisions;

		for (auto& collision : Game::Instance().GetAssetManager().GetAsset<SpriteData>(spriteId)->_collisionShapes)
		{
			//TODO : remove
			if (collision.GetType() == CollisionHitType::Defense)
			{
				continue;
			}

			auto* shape = collision.GetShape();
			if (shape->Type() == ShapeType::RECTANGLE) // TODO: conflict between Rectangle et Rectangle
			{
				const auto* pBox2D = dynamic_cast<const Rectangle*>(shape);
				if (pBox2D != nullptr)
				{
					shape = new Rectangle(pBox2D->x, pBox2D->y, pBox2D->w, pBox2D->h);
				}
			}
			else
			{
				throw Exception("SpritePhysicsHelper::CreateCollisionsFromSprite() shape->Type() is not supported");
			}

			auto* pObj = Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld().CreateSensor(entity, shape, Vector3::Zero(), collision.GetType());

			collisions.push_back(pObj);
		}

		return collisions;
	}

	void SpritePhysicsHelper::AddCollisionFromSprite(ICollisionObjectContainer* collisionObject, const SpriteData* sprite_data, Vector3 translation)
	{
		auto* bt_collision_object = dynamic_cast<BulletCollisionObjectContainer*>(collisionObject)->GetCollisionObject();
		auto* bt_collision_shape = bt_collision_object->getCollisionShape();

		if (bt_collision_shape != nullptr) //btBoxShape works with half length
		{
			auto* bt_box_shape = static_cast<btBoxShape*>(bt_collision_shape);
			if (bt_box_shape != nullptr)
			{
				const auto half_extents_with_margin = bt_box_shape->getHalfExtentsWithMargin();
				translation.x += half_extents_with_margin.x();
				translation.y += half_extents_with_margin.y();
			}
		}
		bt_collision_object->getWorldTransform().setOrigin(btVector3(translation.x - sprite_data->GetOrigin().x, translation.y - sprite_data->GetOrigin().y, translation.z));
		Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld().AddCollisionObject(collisionObject);
	}

	void SpritePhysicsHelper::AddCollisionsFromSprite(Vector3 translation, const std::string& spriteId, const std::vector<ICollisionObjectContainer*>& collisionObjects)
	{
		const auto* sprite_data = Game::Instance().GetAssetManager().GetAsset<SpriteData>(spriteId);

		for (auto* collisionObject : collisionObjects)
		{
			AddCollisionFromSprite(collisionObject, sprite_data, translation);
		}
	}
}
