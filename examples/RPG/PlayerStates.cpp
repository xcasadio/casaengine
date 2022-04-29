#include "PlayerStates.h"
#include "Game\Game.h"
#include "PlayerController.h"
#include "CharacterEnum.h"
#include "GameDatas/MessageType.h"



PlayerStateGlobal::PlayerStateGlobal() = default;

PlayerStateGlobal::~PlayerStateGlobal() = default;

void PlayerStateGlobal::Enter(IController * pController_) {}

void PlayerStateGlobal::Execute(IController * pController_, const GameTime & elpasedTime)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);

	//check dying
	if (pPlayerController->GetPlayer()->IsDead())
	{
		//state dying
		return;
	}
}

void PlayerStateGlobal::Exit(IController * pController_) {}

bool PlayerStateGlobal::OnMessage(IController * pController_, const Telegram & msg)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////


PlayerStateIdle::PlayerStateIdle() = default;

PlayerStateIdle::~PlayerStateIdle() = default;

void PlayerStateIdle::Enter(IController * pController_)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);
	Vector2 joyDir = Vector2::Zero();
	pPlayerController->GetPlayer()->Move(joyDir);
	pPlayerController->GetPlayer()->SetCurrentAnimationByName("swordman_stand");
}

void PlayerStateIdle::Execute(IController * pController_, const GameTime & elpasedTime_)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);

	Vector2 joyDir;
	const orientation dir = pPlayerController->GetDirectionFromInput(joyDir);

	if (dir != 0)
	{
		pPlayerController->GetPlayer()->SetOrientation(dir);
	}

	if (pPlayerController->IsAttackButtonPressed() == true)
	{
		pPlayerController->FSM()->ChangeState(pPlayerController->GetState(ATTACK_1));
		return;
	}

	if (joyDir.x != 0.0f || joyDir.y != 0.0f)
	{
		pPlayerController->GetPlayer()->Move(joyDir);
		pPlayerController->FSM()->ChangeState(pPlayerController->GetState(MOVING));
	}
}

void PlayerStateIdle::Exit(IController * pController_)
{
}

bool PlayerStateIdle::OnMessage(IController * pController_, const Telegram&)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////

PlayerStateWalking::PlayerStateWalking() = default;

PlayerStateWalking::~PlayerStateWalking() = default;

void PlayerStateWalking::Enter(IController * pController_)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);
	pPlayerController->GetPlayer()->SetCurrentAnimationByName("swordman_walk");
}

void PlayerStateWalking::Execute(IController * pController_, const GameTime & elpasedTime_)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);

	Vector2 joyDir;
	const orientation dir = pPlayerController->GetDirectionFromInput(joyDir);

	if (dir != 0)
	{
		pPlayerController->GetPlayer()->SetOrientation(dir);
		pPlayerController->GetPlayer()->SetCurrentAnimationByName("swordman_walk");
	}

	if (pPlayerController->IsAttackButtonPressed() == true)
	{
		pPlayerController->FSM()->ChangeState(pPlayerController->GetState(ATTACK_1));
		return;
	}

	if (joyDir.x != 0.0f || joyDir.y != 0.0f)
	{
		pPlayerController->GetPlayer()->Move(joyDir);
	}
	else
	{
		pPlayerController->FSM()->ChangeState(pPlayerController->GetState(IDLE));
	}
}

void PlayerStateWalking::Exit(IController * pController_)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);
	pPlayerController->GetPlayer()->Move(Vector2::Zero());
}

bool PlayerStateWalking::OnMessage(IController * pController_, const Telegram & msg)
{
	/*
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);

	if (msg.Msg == static_cast<int>(MessageType::ANIMATION_FINISHED))
	{
		pPlayerController->FSM()->ChangeState(pPlayerController->GetState(static_cast<int>(IDLE)));
		return true;
	}
	*/
	return false;
}


//////////////////////////////////////////////////////////////////////////

PlayerStateAttack::PlayerStateAttack() = default;

PlayerStateAttack::~PlayerStateAttack() = default;

void PlayerStateAttack::Enter(IController * pController_)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);
	//equip sword
	pPlayerController->GetPlayer()->AttachWeapon();
	//ranged attack reset

// 	pPlayerController->GetHero()->AttackChargingValue(0.0f);
// 	pPlayerController->GetHero()->IsAttackReleasing(false);
// 	pPlayerController->GetHero()->AttackCharging(false);

	Vector2 joyDir = Vector2::Zero();
	pPlayerController->GetPlayer()->Move(joyDir);
	pPlayerController->GetPlayer()->SetCurrentAnimationByName("swordman_attack");
}

void PlayerStateAttack::Execute(IController * pController_, const GameTime & elpasedTime_)
{
	//PlayerController* pPlayerController = dynamic_cast<PlayerController*>(pController_);

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

void PlayerStateAttack::Exit(IController * pController_)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);

	//unequip sword
	pPlayerController->GetPlayer()->UnAttachWeapon();
}

bool PlayerStateAttack::OnMessage(IController * pController_, const Telegram & msg)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);

	if (msg.Msg == (int)MessageType::ANIMATION_FINISHED)
	{
		//		if (pPlayerController->GetHero()->AttackType() == AttackType::Melee)
		{
			// 			if (pPlayerController->ComboNumber() == 1)
			// 			{
			// 				pPlayerController->FSM()->ChangeState(pPlayerController->GetState((int)PlayerControllerState::ATTACK_2));
			// 			}
			// 			else
			{
				pPlayerController->FSM()->ChangeState(pPlayerController->GetState(IDLE));
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