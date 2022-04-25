#pragma once

#include <map>
#include <queue>

#include "CharacterEnum.h"
#include "Animations\Animation2D.h"
#include "Entities\Component.h"
#include "Entities\Components\AnimatedSpriteComponent.h"
#include "GameDatas/CharacterBase.h"
#include "GameDatas/IController.h"
#include "GameDatas\IGameData.h"
#include "Maths\Vector2.h"
#include "Sprite\Sprite.h"

using namespace CasaEngine;

class Character :
	public CharacterBase
{
public:
	static constexpr int Deadzone = 20;

public:
	~Character() override;

	void Initialize() override;
	void Update(const GameTime& gameTime_) override;
	void Draw() override;
	bool HandleMessage(const Telegram& msg) override;

	void SetAnimationParameters(unsigned int numberOfDir_, unsigned int animationDirMask_);
	void SetAnimationDirectionOffset(orientation dir_, int offset_);

	bool SetCurrentAnimationByName(const char* name);

	bool OnFrameChangedEvent(const EventArgs& e_);
	bool OnAnimationFinished(const EventArgs& e_);

protected:
	Character(BaseEntity* pEntity);

private:
	int GetAnimationDirectionOffset();

	CharacterType m_Type;
	// 	AttackType m_AttackType;
	// 	bool m_IsAttackCharging;
	// 	bool m_IsAttackReleasing;
	// 	float m_AttackChargingValue;
	//
	int m_HPMax;
	int m_HPMaxOffSet;
	int m_HP{};
	int m_HPOffSet;
	//
	int m_MPMax;
	int m_MPMaxOffSet;
	int m_MP{};
	int m_MPOffSet;
	//
	int m_Strength;
	int m_StrengthOffSet;
	int m_Defense{};
	int m_DefenseOffSet;

	//Vector2 m_Velocity;
	int m_ComboNumber{};
	bool m_IsPlayer{};

	//	TeamInfo m_TeamInfo;

	std::map<int, Animation2D*> m_Animations;
	unsigned int m_NumberOfDirection;
	unsigned int m_AnimationDirectionMask;
	std::map<int, int> m_AnimationDirectionOffset;

	//std::vector<Entity *> m_EntityAlreadyAttacked;
	Sprite* m_pLastSprite;
};
