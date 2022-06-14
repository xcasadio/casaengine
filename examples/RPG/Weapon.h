#pragma once

#include "Character.h"
#include "Assets/Assetable.h"
#include "Entities/BaseEntity.h"

using namespace CasaEngine;

class Weapon :
	public IAssetable
{
public:
	Weapon(BaseEntity* entity, Character* owner);
	~Weapon() override = default;

	void Initialize();
	void CollideWith(CollisionParameters* collisionParameters, BaseEntity* otherEntity, CollisionParameters* otherCollisionParameters);
	bool HandleMessage(const Telegram& msg);

private:
	BaseEntity* _entity;
	Character* _owner;
};