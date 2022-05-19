#include "PlayerStates.h"
#include "Game\Game.h"
#include "PlayerController.h"
#include "CharacterEnum.h"
#include "GameDatas/MessageType.h"



PlayerStateGlobal::PlayerStateGlobal() = default;

PlayerStateGlobal::~PlayerStateGlobal() = default;

void PlayerStateGlobal::Enter(IController * controller) {}

void PlayerStateGlobal::Execute(IController * controller, const GameTime & elpasedTime)
{
	auto* playerController = dynamic_cast<PlayerController*>(controller);

	//check dying
	if (playerController->GetPlayer()->IsDead())
	{
		//state dying
		return;
	}
}

void PlayerStateGlobal::Exit(IController * controller) {}

bool PlayerStateGlobal::OnMessage(IController * controller, const Telegram & msg)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////


PlayerStateIdle::PlayerStateIdle() = default;

PlayerStateIdle::~PlayerStateIdle() = default;

void PlayerStateIdle::Enter(IController * controller)
{
	auto* playerController = dynamic_cast<PlayerController*>(controller);
	Vector2 joyDir = Vector2::Zero();
	playerController->GetPlayer()->Move(joyDir);
	playerController->GetPlayer()->SetCurrentAnimationByNameWithOrientation("swordman_stand");
}

void PlayerStateIdle::Execute(IController * controller, const GameTime & elpasedTime_)
{
	auto* playerController = dynamic_cast<PlayerController*>(controller);

	Vector2 joyDir;
	const Orientation dir = playerController->GetDirectionFromInput(joyDir);

	if ((int)dir != 0)
	{
		playerController->GetPlayer()->SetOrientation(dir);
	}

	if (playerController->IsAttackButtonPressed() == true)
	{
		playerController->FSM()->ChangeState(playerController->GetState(ATTACK_1));
		return;
	}

	if (joyDir.x != 0.0f || joyDir.y != 0.0f)
	{
		playerController->GetPlayer()->Move(joyDir);
		playerController->FSM()->ChangeState(playerController->GetState(MOVING));
	}
}

void PlayerStateIdle::Exit(IController * controller)
{
}

bool PlayerStateIdle::OnMessage(IController * controller, const Telegram&)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////

PlayerStateWalking::PlayerStateWalking() = default;

PlayerStateWalking::~PlayerStateWalking() = default;

void PlayerStateWalking::Enter(IController * controller)
{
	auto* playerController = dynamic_cast<PlayerController*>(controller);
	playerController->GetPlayer()->SetCurrentAnimationByNameWithOrientation("swordman_walk");
}

void PlayerStateWalking::Execute(IController * controller, const GameTime & elpasedTime_)
{
	auto* playerController = dynamic_cast<PlayerController*>(controller);

	Vector2 joyDir;
	const Orientation dir = playerController->GetDirectionFromInput(joyDir);

	if ((int)dir != 0)
	{
		playerController->GetPlayer()->SetOrientation(dir);
		playerController->GetPlayer()->SetCurrentAnimationByNameWithOrientation("swordman_walk");
	}

	if (playerController->IsAttackButtonPressed() == true)
	{
		playerController->FSM()->ChangeState(playerController->GetState(ATTACK_1));
		return;
	}

	if (joyDir.x != 0.0f || joyDir.y != 0.0f)
	{
		playerController->GetPlayer()->Move(joyDir);
	}
	else
	{
		playerController->FSM()->ChangeState(playerController->GetState(IDLE));
	}
}

void PlayerStateWalking::Exit(IController * controller)
{
	auto* playerController = dynamic_cast<PlayerController*>(controller);
	playerController->GetPlayer()->Move(Vector2::Zero());
}

bool PlayerStateWalking::OnMessage(IController * controller, const Telegram & msg)
{
	/*
	auto* playerController = dynamic_cast<PlayerController*>(controller);

	if (msg.Msg == static_cast<int>(MessageType::ANIMATION_FINISHED))
	{
		playerController->FSM()->ChangeState(playerController->GetState(static_cast<int>(IDLE)));
		return true;
	}
	*/
	return false;
}


//////////////////////////////////////////////////////////////////////////

PlayerStateAttack::PlayerStateAttack() = default;

PlayerStateAttack::~PlayerStateAttack() = default;

void PlayerStateAttack::Enter(IController * controller)
{
	auto* playerController = dynamic_cast<PlayerController*>(controller);
	//equip sword
	playerController->GetPlayer()->AttachWeapon();
	//ranged attack reset

// 	playerController->GetHero()->AttackChargingValue(0.0f);
// 	playerController->GetHero()->IsAttackReleasing(false);
// 	playerController->GetHero()->AttackCharging(false);

	Vector2 joyDir = Vector2::Zero();
	playerController->GetPlayer()->Move(joyDir);
	playerController->GetPlayer()->SetCurrentAnimationByNameWithOrientation("swordman_attack");
}

void PlayerStateAttack::Execute(IController * controller, const GameTime & elpasedTime_)
{
	//PlayerController* playerController = dynamic_cast<PlayerController*>(controller);

	//if (playerController->GetHero()->AttackType() == Character::AttackType::Melee)
	{
		//         if (playerController->GetHero()->ComboNumber() == 0
		//             && playerController->GetHero()->Animation2DPlayer.CurrentAnimation.CurrentFrameIndex >= 4
		//             && playerController->IsAttackButtonPressed() == true)
		//         {
		//             playerController->GetHero()->SetComboNumber(1);
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

void PlayerStateAttack::Exit(IController * controller)
{
	auto* playerController = dynamic_cast<PlayerController*>(controller);

	//unequip sword
	playerController->GetPlayer()->UnAttachWeapon();
}

bool PlayerStateAttack::OnMessage(IController * controller, const Telegram & msg)
{
	auto* playerController = dynamic_cast<PlayerController*>(controller);

	if (msg.Msg == (int)MessageType::ANIMATION_FINISHED)
	{
		//		if (playerController->GetHero()->AttackType() == AttackType::Melee)
		{
			// 			if (playerController->ComboNumber() == 1)
			// 			{
			// 				playerController->FSM()->ChangeState(playerController->GetState((int)PlayerControllerState::ATTACK_2));
			// 			}
			// 			else
			{
				playerController->FSM()->ChangeState(playerController->GetState(IDLE));
			}
		}
		// 		else // ranged attack
		// 		{
		// 			//if (charac.IsAttackReleasing == true)
		// 			//{
		// 			playerController->FSM()->ChangeState(playerController->GetState((int)PlayerControllerState::ATTACK_2));
		// 			//}
		// 			//else
		// 			//{
		// 			playerController->GetHero()->IsAttackCharging(true);
		// 			//}
		// 		}

		return true;
	}

	return false;
}