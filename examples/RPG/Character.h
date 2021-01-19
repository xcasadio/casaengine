#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Entities\Component.h"
#include <map>
#include "CharacterEnum.h"
#include "Maths\Vector2.h"
#include "IController.h"
#include "Animations\Animation2D.h"
#include "Data\IGameData.h"
#include "Entities\Components\AnimatedSpriteComponent.h"
#include <queue>

#include "Sprite\Sprite.h"
#include "Entities\BaseEntity.h"

using namespace CasaEngine;

/**
 *
 */
class Character :
	public IGameData
{
public:
	// Index of character animation.
	// Respect the order of the enum CharacterAnimation
	enum class AnimationIndices
	{
		IDLE = 0,
		RUN = 1,
		ATTACK1 = 2,
		ATTACK2 = 3,
		ATTACK3 = 4,
		HIT = 5,
		MAGIC1 = 6,
		MAGIC2 = 7,
		DYING = 8,
		DEAD = 9,
		TO_RAGE = 10,
		TO_NORMAL = 11,

		//FuryModeOffset, //use to set animation
		//respect the order : same as "normal mode"
		FURY_IDLE = 12,
		FURY_RUN = 13,
		FURY_ATTACK1 = 14,
		FURY_ATTACK2 = 15,
		FURY_ATTACK3 = 16,
		FURY_HIT = 17,
		FURY_MAGIC1 = 18,
		FURY_MAGIC2 = 19,
		FURY_DYING = 20,
		FURY_DEAD = 21,
	};

	// Respect the order of the enum CharacterAnimation
	enum class AnimationDirectionOffset
	{
		RIGHT = 0,
		LEFT = 1,
		UP = 2,
		DOWN = 3,
		UP_RIGHT = 4,
		DOWN_RIGHT = 5,
		UP_LEFT = 6,
		DOWN_LEFT = 7,
	};

public:

	static const int Deadzone = 20;
	static orientation GetOrientationFromVector2(Vector2F v);

public:
	virtual ~Character();

	virtual void Initialize();
	void Update(const GameTime& gameTime_);
	void Draw();
	virtual bool HandleMessage(const Telegram& msg);

	void SetAnimationParameters(unsigned int numberOfDir_, unsigned int animationDirMask_);
	void SetAnimationDirectionOffset(orientation dir_, int offset_);

	/**
	 * Set the animation compared to the index and the direction of the character
	 * See AnimationDirectionMask, CharacterDirection, AnimationIndices, NumberCharacterDriection
	 */
	void SetCurrentAnimation(int index_);
	void SetCurrentAnimation(const char* name) const;
	bool SetCurrentAnimationByName(const char* name);

	IController* GetController() const;

	bool OnFrameChangedEvent(const EventArgs& e_);
	bool OnAnimationFinished(const EventArgs& e_);

	void Move(Vector2F& dir);

	Vector2F Direction() const;
	void Direction(Vector2F val);

	orientation GetOrientation() const;
	void SetOrientation(orientation val);

protected:
	Character(BaseEntity* pEntity);

private:
	int GetAnimationDirectionOffset();

protected:
	IController* m_pController;

private:
	CharacterType m_Type;
	// 	AttackType m_AttackType;
	// 	bool m_IsAttackCharging;
	// 	bool m_IsAttackReleasing;
	// 	float m_AttackChargingValue;

	float m_Speed;
	float m_SpeedOffSet;
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

	//Vector2F m_Velocity;

	orientation m_Orientation;
	Vector2F m_Direction;
	int m_ComboNumber;
	bool m_IsPlayer;

	//	TeamInfo m_TeamInfo;

	std::map<int, Animation2D*> m_Animations;
	unsigned int m_NumberOfDirection;
	unsigned int m_AnimationDirectioMask;
	std::map<int, int> m_AnimationDirectionOffset;

	//std::vector<Entity *> m_EntityAlreadyAttacked;

	BaseEntity* m_pEntity;
	AnimatedSpriteComponent* m_pAnimatedSprite;
	Sprite* m_pLastSprite;

	std::queue<Telegram> m_MessageQueue;
};

#endif
