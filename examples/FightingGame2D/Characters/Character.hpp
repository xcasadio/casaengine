#pragma once

#include  "GameDatas/CharacterBase.hpp"
#include  "GameDatas/Character2DBase.hpp"
#include  "Entities/BaseEntity.hpp"
#include  "GameTime.hpp"

using namespace CasaEngine;

class Character :
	public Character2DBase
{
public:
	static const int Deadzone = 20;

public:
	~Character() override;

	void Initialize() override;
	void Update(const GameTime& gameTime) override;
	void Draw() override;

protected:
	Character(BaseEntity* pEntity);

	void CollideWith(CollisionParameters* collisionParameters, BaseEntity* otherEntity, CollisionParameters* otherCollisionParameters) override;

private:
	int m_HPMax;
	int m_HP;
	//
	int m_MPMax;
	int m_MP;
};
