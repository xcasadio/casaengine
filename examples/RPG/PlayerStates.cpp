#include "Base.h"
#include "PlayerStates.h"
#include "Game\Game.h"
#include "CA_Assert.h"
#include "PlayerController.h"
#include "CharacterEnum.h"
#include "MessageType.h"


//////////////////////////////////////////////////////////////////////////

/**
 *
 */
PlayerStateIdle::PlayerStateIdle()
{
}

/**
 *
 */
PlayerStateIdle::~PlayerStateIdle()
{

}

/**
 *
 */
void PlayerStateIdle::Enter(IController* pController_)
{
	PlayerController* pPlayerController = dynamic_cast<PlayerController*>(pController_);

	//TODO selon la direction definir l'animation
	Vector2F joyDir = Vector2F::Zero();
	pPlayerController->GetHero()->Move(joyDir);

	if (pPlayerController->GetHero()->InFuryMode() == true)
	{
		pPlayerController->GetHero()->SetCurrentAnimation(static_cast<int>(Character::AnimationIndices::FURY_IDLE));
	}
	else
	{
		pPlayerController->GetHero()->SetCurrentAnimation(static_cast<int>(Character::AnimationIndices::IDLE));
	}
}

/**
 *
 */
void PlayerStateIdle::Execute(IController* pController_, const GameTime& elpasedTime_)
{
	PlayerController* pPlayerController = dynamic_cast<PlayerController*>(pController_);
	//PlayerIndex playerIndex = c.PlayerIndex;

	orientation dir;
	Vector2F joyDir;

	if (pPlayerController->GetHero()->FuryModeEnabling() == true)
	{
		pPlayerController->FSM()->ChangeState(pPlayerController->GetState(static_cast<int>(TO_FURY_MODE)));
		return;
	}
	else if (pPlayerController->GetHero()->FuryModeDesabling() == true)
	{
		pPlayerController->FSM()->ChangeState(pPlayerController->GetState(static_cast<int>(TO_NORMAL_MODE)));
		return;
	}
	else if (pPlayerController->IsAttackButtonPressed() == true)
	{
		pPlayerController->FSM()->ChangeState(pPlayerController->GetState(static_cast<int>(ATTACK_1)));
		return;
	}

	dir = pPlayerController->GetDirectionFromInput(joyDir);

	if (dir != 0)
	{
		pPlayerController->GetHero()->SetOrientation(dir);
	}

	if (joyDir.x != 0.0f || joyDir.y != 0.0f)
	{
		//pPlayerController->FSM()->ChangeState(pPlayerController->GetState((int)PlayerControllerState::MOVING));
		//return;
		/*if (charac.InFuryMode == true)
		{
			controller.Character.SetCurrentAnimation((int)Character.Character.AnimationIndices.FuryModeRun);
		}
		else
		{*/
		pPlayerController->GetHero()->Move(joyDir);
		//pPlayerController->GetHero()->SetCurrentAnimation(static_cast<int>(Character::AnimationIndices::RUN));
		pPlayerController->GetHero()->SetCurrentAnimationByName("walk");
		//}

	}
	else // used to immobilized the character
	{
		joyDir = Vector2F::Zero();
		pPlayerController->GetHero()->Move(joyDir);

		//pPlayerController->GetHero()->SetCurrentAnimation(static_cast<int>(Character::AnimationIndices::IDLE));
		pPlayerController->GetHero()->SetCurrentAnimationByName("stand");
	}
}

/**
 *
 */
void PlayerStateIdle::Exit(IController* pController_)
{

}

/**
 *
 */
bool PlayerStateIdle::OnMessage(IController* pController_, const Telegram&)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////

/**
 *
 */
PlayerStateAttack::PlayerStateAttack()
{
}

/**
 *
 */
PlayerStateAttack::~PlayerStateAttack()
{

}

/**
 *
 */
void PlayerStateAttack::Enter(IController* pController_)
{
	PlayerController* pPlayerController = dynamic_cast<PlayerController*>(pController_);

	//ranged attack reset
// 	pPlayerController->GetHero()->AttackChargingValue(0.0f);
// 	pPlayerController->GetHero()->IsAttackReleasing(false);
// 	pPlayerController->GetHero()->AttackCharging(false);

	if (pPlayerController->GetHero()->FuryModeDesabling() == true)
	{
		pPlayerController->FSM()->ChangeState(pPlayerController->GetState(static_cast<int>(TO_NORMAL_MODE)));
		return;
	}

	// 	pPlayerController->GetHero()->DoANewAttack();
	// 	pPlayerController->GetHero()->SetComboNumber(0);
	Vector2F joyDir = Vector2F::Zero();
	pPlayerController->GetHero()->Move(joyDir);

	if (pPlayerController->GetHero()->InFuryMode() == true)
	{
		pPlayerController->GetHero()->SetCurrentAnimation(static_cast<int>(Character::AnimationIndices::FURY_ATTACK1));
	}
	else
	{
		pPlayerController->GetHero()->SetCurrentAnimation(static_cast<int>(Character::AnimationIndices::ATTACK1));
	}
}

/**
 *
 */
void PlayerStateAttack::Execute(IController* pController_, const GameTime& elpasedTime_)
{
	PlayerController* pPlayerController = dynamic_cast<PlayerController*>(pController_);

	//if (pPlayerController->GetHero()->AttackType() == Character::AttackType::Melee)
	{
		//         if (pPlayerController->GetHero()->ComboNumber() == 0
		//             && pPlayerController->GetHero()->Animation2DPlayer.CurrentAnimation.CurrentFrameIndex >= 4
		//             && pPlayerController->IsAttackButtonPressed() == true)
		//         {
		//             pPlayerController->GetHero()->SetComboNumber(1);
		//         }
	}
	//     else
	//     {
	//         if (c.IsAttackButtonPressed(false) == true
	//             && charac.IsAttackCharging == true
	//             && charac.IsAttackReleasing == false)
	//         {
	//             charac.AttackChargingValue += elpasedTime_;
	//         }
	//         else if (c.IsAttackButtonPressed(false) == false)
	//         {
	//             charac.IsAttackReleasing = true;
	//         }
	//     }
}

/**
 *
 */
void PlayerStateAttack::Exit(IController* pController_)
{

}

/**
 *
 */
bool PlayerStateAttack::OnMessage(IController* pController_, const Telegram& msg)
{
	PlayerController* pPlayerController = dynamic_cast<PlayerController*>(pController_);

	if (msg.Msg == ANIMATION_FINISHED)
	{
		//		if (pPlayerController->GetHero()->AttackType() == AttackType::Melee)
		{
			// 			if (pPlayerController->ComboNumber() == 1)
			// 			{
			// 				pPlayerController->FSM()->ChangeState(pPlayerController->GetState((int)PlayerControllerState::ATTACK_2));
			// 			}
			// 			else
			{
				pPlayerController->FSM()->ChangeState(pPlayerController->GetState(static_cast<int>(IDLE)));
			}
		}
		// 		else // ranged attack
		// 		{
		// 			//if (charac.IsAttackReleasing == true)
		// 			//{
		// 			pPlayerController->FSM()->ChangeState(pPlayerController->GetState((int)PlayerControllerState::ATTACK_2));
		// 			//}
		// 			//else
		// 			//{
		// 			pPlayerController->GetHero()->IsAttackCharging(true);
		// 			//}                    
		// 		}

		return true;
	}

	return false;
}
