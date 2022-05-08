#pragma once

#include <string>

#include "CharacterEnum.h"
#include "Animations\Animation2D.h"
#include "Entities\Component.h"
#include "Entities\Components\AnimatedSpriteComponent.h"
#include "GameDatas/CharacterBase.h"
#include "GameDatas/IController.h"
#include "GameDatas\IGameData.h"
#include "Maths\Vector2.h"
#include "Sprite\Sprite.h"
#include "GameDatas\Character2DBase.h"

using namespace CasaEngine;

class Character :
	public Character2DBase
{
public:
	static constexpr int Deadzone = 20;

public:
	~Character() override;

	void Initialize() override;
	void Update(const GameTime& gameTime_) override;
	void Draw() override;

	bool IsDead() const;

protected:
	Character(BaseEntity* pEntity);

	void CollideWith(BaseEntity* otherEntity, CollisionParametersBetween2Entities* collisionParams) override;

private:	

	CharacterType m_Type;
	// 	AttackType m_AttackType;
	// 	bool m_IsAttackCharging;
	// 	bool m_IsAttackReleasing;
	// 	float m_AttackChargingValue;
	//
	int m_HPMax;
	int m_HPMaxOffSet;
	int m_HP;
	int m_HPOffSet;
	//
	int m_MPMax;
	int m_MPMaxOffSet;
	int m_MP;
	int m_MPOffSet;
	//
	int m_Strength;
	int m_StrengthOffSet;
	int m_Defense;
	int m_DefenseOffSet;

	//Vector2 m_Velocity;
	int m_ComboNumber;
	//	TeamInfo m_TeamInfo;

	//std::vector<Entity *> m_EntityAlreadyAttacked;
};
