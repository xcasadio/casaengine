#include "ScriptGrass.h"

#include "Game/Game.h"
#include "GameDatas/MessageType.h"
#include "Map2D/AutoTile.h"
#include "Map2D/EmptyTile.h"
#include "Map2D/TileComponent.h"
#include "Physics/CollisionParametersBetween2Entities.h"

ScriptGrass::ScriptGrass(BaseEntity* entity) :
	IScriptObject(entity)
{
}

ScriptGrass::~ScriptGrass() = default;

void ScriptGrass::OnInitialize()
{
}

void ScriptGrass::OnUpdate(const GameTime& gameTime_)
{
}

bool ScriptGrass::HandleMessage(const Telegram& msg)
{
	if (msg.ExtraInfo != nullptr
		&& msg.Msg == (int)MessageType::COLLISION
		&& (GetEntity()->Id() == msg.Sender || GetEntity()->Id() == msg.Receiver)
		&& msg.Sender != msg.Receiver)
	{
		auto* otherEntity = GetEntity()->Id() == msg.Sender ? Game::Instance().GetEntityManager().GetEntityFromID(msg.Receiver) : Game::Instance().GetEntityManager().GetEntityFromID(msg.Sender);
		auto* collisionParameters = static_cast<CollisionParametersBetween2Entities*>(msg.ExtraInfo);

		CollideWith(
			collisionParameters->CollisionParameters1()->GetEntity()->Id() == GetEntity()->Id() ? collisionParameters->CollisionParameters1() : collisionParameters->CollisionParameters2(),
			otherEntity,
			collisionParameters->CollisionParameters1()->GetEntity()->Id() == otherEntity->Id() ? collisionParameters->CollisionParameters1() : collisionParameters->CollisionParameters2());
	}

	return false;
}

void ScriptGrass::OnDestroy()
{
}

void ScriptGrass::CollideWith(CollisionParameters* collisionParameters, BaseEntity* otherEntity, CollisionParameters* otherCollisionParameters)
{
	auto* tile_component = GetEntity()->GetComponentMgr()->GetComponent<TileComponent>();

	if (otherCollisionParameters->GetCollision()->GetType() == CollisionHitType::Attack && tile_component != nullptr)
	{
		auto* auto_tile = (AutoTile*)tile_component->Tile();
		if (auto_tile != nullptr)
		{
			tile_component->Tile(new EmptyTile());
			auto_tile->RemovedTileFromLayer();
		}
	}
}
