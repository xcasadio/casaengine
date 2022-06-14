#include "Base.h"
#include "Weapon.h"

#include "Game/Game.h"
#include "GameDatas/MessageType.h"
#include "Map2D/AutoTile.h"
#include "Map2D/TileComponent.h"


Weapon::Weapon(BaseEntity* entity, Character* owner) :
	_entity(entity),
	_owner(owner)
{
}

void Weapon::Initialize()
{
	//SetController(::new PlayerController(this, 0));
	//Character::Initialize();
}
bool Weapon::HandleMessage(const Telegram& msg)
{
	if (msg.ExtraInfo != nullptr
		&& msg.Msg == (int)MessageType::COLLISION
		&& (_entity->Id() == msg.Sender || _entity->Id() == msg.Receiver)
		&& msg.Sender != msg.Receiver)
	{
		auto* otherEntity = _entity->Id() == msg.Sender ? Game::Instance().GetEntityManager().GetEntityFromId(msg.Receiver) : Game::Instance().GetEntityManager().GetEntityFromId(msg.Sender);
		auto* collisionParameters = static_cast<CollisionParametersBetween2Entities*>(msg.ExtraInfo);

		CollideWith(
			collisionParameters->CollisionParameters1()->GetEntity()->Id() == _entity->Id() ? collisionParameters->CollisionParameters1() : collisionParameters->CollisionParameters2(),
			otherEntity,
			collisionParameters->CollisionParameters1()->GetEntity()->Id() == otherEntity->Id() ? collisionParameters->CollisionParameters1() : collisionParameters->CollisionParameters2());
	}

	return false;
}

void Weapon::CollideWith(CollisionParameters* collisionParameters, BaseEntity* otherEntity,
	CollisionParameters* otherCollisionParameters)
{
	//hit by other
	if (collisionParameters->GetCollision()->GetType() == CollisionHitType::Defense
		&& otherCollisionParameters->GetCollision()->GetType() == CollisionHitType::Attack)
	{
		//auto* scriptComponent = otherEntity->GetComponentMgr()->GetComponent<ScriptComponent>();
		//if (scriptComponent != nullptr)
		//{
		//	auto* script_character = dynamic_cast<ScriptCharacter*>(scriptComponent->GetScriptObject());
		//
		//	if (script_character != nullptr)
		//	{
		//		auto* otherCharacter = script_character->GetCharacter();
		//
		//		//state hit
		//		//HitBy(otherCharacter);
		//	}
		//}
	}
	//hit other
	else if (collisionParameters->GetCollision()->GetType() == CollisionHitType::Attack
		&& otherCollisionParameters->GetCollision()->GetType() == CollisionHitType::Defense)
	{
		//auto* scriptComponent = otherEntity->GetComponentMgr()->GetComponent<ScriptComponent>();
		//if (scriptComponent != nullptr)
		//{
		//	auto* scriptObject = scriptComponent->GetScriptObject();
		//	if (scriptObject != nullptr)
		//	{
		//		//Hit(scriptObject); // par exemple tile
		//	}
		//}

		//auto* tileMap = otherEntity->GetComponentMgr()->GetComponent<TileComponent>();
		//tileMap->
		auto* tileComponent = otherEntity->GetComponentMgr()->GetComponent<TileComponent>();
		if (tileComponent != nullptr)
		{
			if (tileComponent->Tile()->GetTileData()->isBreakable)
			{
				otherEntity->ToRemoved(true);

				auto* auto_tile = dynamic_cast<AutoTile*>(tileComponent->Tile());
				if (auto_tile)
				{
					auto_tile->RemovedTileFromLayer();
				}
			}

			
		}
	}

	//si je suis une arme alors c'est le parent que je dois invoquer
	//creer un character pour l'arme du coup
	//TODO : creer GetScriptObject pour l'arme qui appelera le character parent
	//if (otherEntity->GetParent() != nullptr)
	//{
	//	otherEntity = otherEntity->GetParent();
	//}

	//auto* scriptComponent = otherEntity->GetComponentMgr()->GetComponent<ScriptComponent>();
	//if (scriptComponent != nullptr)
	//{
	//	auto* script_character = dynamic_cast<ScriptCharacter*>(scriptComponent->GetScriptObject());
	//
	//	if (script_character != nullptr)
	//	{
	//		auto* otherCharacter = script_character->GetCharacter();
	//
	//
	//	}
	//}
}

