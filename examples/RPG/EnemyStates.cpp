#include "EnemyStates.h"

#include "CharacterEnum.h"
#include "Game\Game.h"

/**
 *
 */
EnemyStateIdle::EnemyStateIdle()
{
}

/**
 *
 */
EnemyStateIdle::~EnemyStateIdle()
{
}

/**
 *
 */
void EnemyStateIdle::Enter(IController* pController_)
{
	pController_->GetCharacter()->Move(Vector2F::Zero());
	pController_->GetCharacter()->SetOrientation(orientation::RIGHT);
	//set animation stand
	/*orientation dir = (orientation)(1 << (rand() % 4));
	pController_->GetCharacter()->SetOrientation(dir);*/
	//pController_->GetCharacter()->SetCurrentAnimation(static_cast<int>(Character::AnimationIndices::IDLE));
	pController_->GetCharacter()->SetCurrentAnimationByName("octopus_stand");
}

/**
 *
 */
void EnemyStateIdle::Execute(IController* pController_, const GameTime& elpasedTime_)
{
	//delay action

	if (false)//can attack)
	{
		//e->mov = ATTACK;
	}
	else if (rand() % 100 == 7)
	{
		orientation dir = (orientation)(1 << (rand() % 4));
		pController_->GetCharacter()->SetOrientation(dir);
		//pController_->GetCharacter()->SetCurrentAnimation(static_cast<int>(Character::AnimationIndices::IDLE));
		pController_->GetCharacter()->SetCurrentAnimationByName("octopus_stand");
	}
	else if (rand() % 100 == 8)
	{
		pController_->FSM()->ChangeState(pController_->GetState(static_cast<int>(EnemyControllerState::MOVING)));
	}
}

/**
 *
 */
void EnemyStateIdle::Exit(IController* pController_)
{
}

/**
 *
 */
bool EnemyStateIdle::OnMessage(IController* pController_, const Telegram&)
{
	return false;
}

/**
 *
 */
EnemyStateWalking::EnemyStateWalking()
{
}

/**
 *
 */
EnemyStateWalking::~EnemyStateWalking()
{
}

/**
 *
 */
void EnemyStateWalking::Enter(IController* pController_)
{
	//set animation stand
	//pController_->GetCharacter()->SetCurrentAnimation(static_cast<int>(Character::AnimationIndices::RUN)); // direction
	pController_->GetCharacter()->SetCurrentAnimationByName("octopus_walk");
}

/**
 *
 */
void EnemyStateWalking::Execute(IController* pController_, const GameTime& elpasedTime_)
{
	//arrive to the target
	auto dir = pController_->GetCharacter()->GetOrientation();
	Vector2F newDir;

	switch (dir)
	{
	case UP: newDir = -Vector2F::UnitY();
		break;
	case DOWN: newDir = Vector2F::UnitY();
		break;
	case LEFT: newDir = -Vector2F::UnitX();
		break;
	case RIGHT: newDir = Vector2F::UnitX();
		break;
		/*case UP_LEFT: newDir = -Vector2F::UnitY() - Vector2F::UnitX();
			break;
		case DOWN_LEFT: newDir = Vector2F::UnitY() - Vector2F::UnitX();
			break;
		case UP_RIGHT: newDir = -Vector2F::UnitY() + Vector2F::UnitX();
			break;
		case DOWN_RIGHT: newDir = Vector2F::UnitY() + Vector2F::UnitX();
			break;*/
	default:
		break;
	}
	pController_->GetCharacter()->Move(newDir);

	if (rand() % 100 == 7)
	{
		pController_->FSM()->ChangeState(pController_->GetState(static_cast<int>(EnemyControllerState::IDLE)));
	}
}

/**
 *
 */
void EnemyStateWalking::Exit(IController* pController_)
{
}

/**
 *
 */
bool EnemyStateWalking::OnMessage(IController* pController_, const Telegram&)
{
	//end animation?
	return false;
}