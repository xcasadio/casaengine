#pragma once

#include "GameDatas/CharacterBase.h"
#include "GameDatas\Character2DBase.h"
#include "Entities\BaseEntity.h"
#include "GameTime.h"

using namespace CasaEngine;

class Character :
	public Character2DBase
{
public:
	static const int Deadzone = 20;

public:
	~Character() override;

	void Initialize() override;
	void Update(const GameTime& gameTime_) override;
	void Draw() override;

protected:
	Character(BaseEntity* pEntity);

	void CollideWith(BaseEntity* otherEntity, CollisionParametersBetween2Entities* collisionParams) override;

private:
	int m_HPMax;
	int m_HP;
	//
	int m_MPMax;
	int m_MP;
};
