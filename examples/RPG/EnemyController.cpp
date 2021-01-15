#include "Base.h"
#include "Game\Game.h"
#include "CharacterEnum.h"
#include "Character.h"
#include "EnemyController.h"
#include "EnemyStates.h"


/**
 *
 */
EnemyController::EnemyController(Character* pCharacter):
	IController(pCharacter)
{
}

/**
 *
 */
EnemyController::~EnemyController()
{

}

/**
 *
 */
void EnemyController::Initialize()
{
	auto state_idle = NEW_AO EnemyStateIdle();
	auto state_walking = NEW_AO EnemyStateWalking();
	//auto state_attack = NEW_AO PlayerStateAttack();
	
	AddState(static_cast<int>(EnemyControllerState::IDLE), state_idle);
	AddState(static_cast<int>(EnemyControllerState::MOVING), state_walking);
	//AddState((int)EnemyControllerState::ATTACK_1, state_attack);
	// 	AddState((int)EnemyControllerState::ATTACK_2, new PlayerAttack2State());
	// 	AddState((int)EnemyControllerState::ATTACK_3, new PlayerAttack3State());
	// 	AddState((int)EnemyControllerState::TO_FURY_MODE, new PlayerToFuryState());
	// 	AddState((int)EnemyControllerState::TO_NORMAL_MODE, new PlayerToNormalState());

	//GetCharacter()->SetOrientation(orientation::RIGHT);
	//Character.Animation2DPlayer.SetCurrentAnimationByID((int)AnimationIndex.IdleRight);
	FSM()->ChangeState(GetState(static_cast<int>(EnemyControllerState::IDLE)));
}

/**
 *
 */
void EnemyController::Update(const GameTime elapsedTime_)
{
	//if (m_InputComponent.IsGamePadConnected(m_PlayerIndex) == true)
	{
		/*if (m_InputComponent.IsButtonJustPressed(m_PlayerIndex, Buttons.RightShoulder)
			|| m_InputComponent.IsKeyJustPressed(Keys.B))
		{
			CheckAndEnableFuryMode();
		}*/
	}

	IController::Update(elapsedTime_);
}
