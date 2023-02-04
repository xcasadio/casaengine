#include "PlayerStates.h"
#include "Game/Game.h"
#include "PlayerController.h"



PlayerStateIdle::PlayerStateIdle()
{
}

PlayerStateIdle::~PlayerStateIdle()
{
}

void PlayerStateIdle::Enter(IController* pController_)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);

	Vector2 joyDir = Vector2::Zero();
	pPlayerController->GetPlayer()->Move(joyDir);
	pPlayerController->GetPlayer()->SetCurrentAnimationByName("idle");
}

void PlayerStateIdle::Execute(IController* pController_, const GameTime& elpasedTime_)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);
	//PlayerIndex playerIndex = c.PlayerIndex;

	Vector2 joyDir;

	if (pPlayerController->IsAttackButtonPressed() == true)
	{
		pPlayerController->FSM()->ChangeState(pPlayerController->GetState(ATTACK_1));
		return;
	}

	const Orientation dir = pPlayerController->GetDirectionFromInput(joyDir);

	if ((int)dir != 0)
	{
		pPlayerController->GetPlayer()->SetOrientation(dir);
	}

	if (joyDir.x != 0.0f || joyDir.y != 0.0f)
	{
		pPlayerController->FSM()->ChangeState(pPlayerController->GetState(PlayerControllerState::MOVING));
	}
	else // used to immobilized the character
	{
		joyDir = Vector2::Zero();
		pPlayerController->GetPlayer()->Move(joyDir);
		pPlayerController->GetPlayer()->SetCurrentAnimationByName("idle");
	}
}

void PlayerStateIdle::Exit(IController* pController_)
{
}

bool PlayerStateIdle::OnMessage(IController* pController_, const Telegram&)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////


PlayerStateWalking::PlayerStateWalking()
{
}

PlayerStateWalking::~PlayerStateWalking()
{
}

void PlayerStateWalking::Enter(IController* pController_)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);

	Vector2 joyDir;
	pPlayerController->GetDirectionFromInput(joyDir);

	if (joyDir.x != 0.0f || joyDir.y != 0.0f)
	{
		pPlayerController->GetPlayer()->Move(joyDir);

		if (joyDir.x > 0.0f)
			pPlayerController->GetPlayer()->SetCurrentAnimationByName("walk_forward");
		else
			pPlayerController->GetPlayer()->SetCurrentAnimationByName("walk_backward");
	}
}

void PlayerStateWalking::Execute(IController* pController_, const GameTime& elpasedTime_)
{
	auto* pPlayerController = dynamic_cast<PlayerController*>(pController_);
	Vector2 joyDir;
	pPlayerController->GetDirectionFromInput(joyDir);

	if (joyDir.x != 0.0f || joyDir.y != 0.0f)
	{
		pPlayerController->GetPlayer()->Move(joyDir);

		if (joyDir.x > 0.0f)
			pPlayerController->GetPlayer()->SetCurrentAnimationByName("walk_forward");
		else
			pPlayerController->GetPlayer()->SetCurrentAnimationByName("walk_backward");
	}
	else
	{
		pPlayerController->FSM()->ChangeState(pPlayerController->GetState(PlayerControllerState::IDLE));
	}
}

void PlayerStateWalking::Exit(IController* pController_)
{
}

bool PlayerStateWalking::OnMessage(IController* pController_, const Telegram& msg)
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