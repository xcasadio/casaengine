#include "Base.h"
#include "PlayerController.h"
#include "Game\Game.h"
#include "CA_Assert.h"
#include "PlayerStates.h"
#include "CharacterEnum.h"
#include "Character.h"

/**
 *
 */
PlayerController::PlayerController(Player* pHero_, PlayerIndex index_) :
	IController(pHero_)
{
	m_PlayerIndex = index_;
	m_pHero = pHero_;
	//pEntity_->IsPlayer(true);

	CA_ASSERT(m_pHero != nullptr, ":PlayerController() : Player is null");
}

/**
 *
 */
PlayerController::~PlayerController()
{
}

/**
 *
 */
void PlayerController::Initialize()
{
	auto player_state_idle = new PlayerStateIdle();
	auto player_state_attack = new PlayerStateAttack();

	AddState(IDLE, player_state_idle);
	// 	AddState((int)PlayerControllerState::MOVING, new PlayerRunState());
	AddState(ATTACK_1, player_state_attack);
	// 	AddState((int)PlayerControllerState::ATTACK_2, new PlayerAttack2State());
	// 	AddState((int)PlayerControllerState::ATTACK_3, new PlayerAttack3State());
	// 	AddState((int)PlayerControllerState::TO_FURY_MODE, new PlayerToFuryState());
	// 	AddState((int)PlayerControllerState::TO_NORMAL_MODE, new PlayerToNormalState());

	GetPlayer()->SetOrientation(RIGHT);
	//Character.Animation2DPlayer.SetCurrentAnimationByID((int)AnimationIndex.IdleRight);
	FSM()->SetCurrentState(GetState(IDLE));
}

/**
 *
 */
void PlayerController::Update(const GameTime elapsedTime_)
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

/**
 *
 */
bool PlayerController::IsAttackButtonJustPressed()
{
	// 	if (m_InputComponent.IsGamePadConnected(m_PlayerIndex) == true)
	// 	{
	// 		return m_InputComponent.IsButtonJustPressed(m_PlayerIndex, Buttons.A);
	// 	}
	return Game::Instance().GetInput().IsKeyJustDown(sf::Keyboard::Space);
}

/**
 *
 */
bool PlayerController::IsAttackButtonPressed()
{
	/*if (m_InputComponent.IsGamePadConnected(m_PlayerIndex) == true)
	{
		return m_InputComponent.IsButtonPressed(m_PlayerIndex, Buttons.A);
	}*/
	return Game::Instance().GetInput().IsKeyDown(sf::Keyboard::Space);
}

/**
 *
 */
orientation PlayerController::GetDirectionFromInput(Vector2F& direction_)
{
	direction_ = Vector2F::Zero();

	if (Game::Instance().GetInput().IsKeyDown(sf::Keyboard::Z) == true
		|| Game::Instance().GetInput().GetJoystickLeftStickY(0) > Character::Deadzone)
	{
		direction_.y = -1.0f;
	}
	else if (Game::Instance().GetInput().IsKeyDown(sf::Keyboard::S) == true
		|| Game::Instance().GetInput().GetJoystickLeftStickY(0) < -Character::Deadzone)
	{
		direction_.y = 1.0f;
	}

	if (Game::Instance().GetInput().IsKeyDown(sf::Keyboard::D) == true
		|| Game::Instance().GetInput().GetJoystickLeftStickX(0) < -Character::Deadzone)
	{
		direction_.x = 1.0f;
	}
	else if (Game::Instance().GetInput().IsKeyDown(sf::Keyboard::Q) == true
		|| Game::Instance().GetInput().GetJoystickLeftStickX(0) > Character::Deadzone)
	{
		direction_.x = -1.0f;
	}

	direction_.Normalize();

	Vector2F vec = direction_;
	//vec.y = -vec.y; //inverse to be on screen coordinate
	return Character::GetOrientationFromVector2(vec);
}

/**
 *
 */
Player* PlayerController::GetPlayer() const
{
	return m_pHero;
}