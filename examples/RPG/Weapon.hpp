#pragma once

#include  "Character.hpp"
#include  "Assets/Assetable.hpp"
#include  "Entities/BaseEntity.hpp"

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