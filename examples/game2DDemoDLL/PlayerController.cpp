
#include "Base.h"
#include "PlayerController.h"
#include "Game\Game.h"
#include "CA_Assert.h"
#include "PlayerStates.h"
#include "CharacterEnum.h"
#include "Character.h"

PlayerStateIdle s_stateIdle;
PlayerStateAttack s_stateAttack1;

/**
 * 
 */
PlayerController::PlayerController(Hero *pHero_, PlayerIndex index_)
{
	m_PlayerIndex = index_;
	m_pHero = pHero_;
	//pEntity_->IsPlayer(true);

	CA_ASSERT(m_pHero != nullptr, ":PlayerController() : Hero is null");
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
	AddState((int)PlayerControllerState::IDLE, &s_stateIdle);
// 	AddState((int)PlayerControllerState::MOVING, new PlayerRunState());
 	AddState((int)PlayerControllerState::ATTACK_1, &s_stateAttack1);
// 	AddState((int)PlayerControllerState::ATTACK_2, new PlayerAttack2State());
// 	AddState((int)PlayerControllerState::ATTACK_3, new PlayerAttack3State());
// 	AddState((int)PlayerControllerState::TO_FURY_MODE, new PlayerToFuryState());
// 	AddState((int)PlayerControllerState::TO_NORMAL_MODE, new PlayerToNormalState());

	GetHero()->SetOrientation(Orientation::RIGHT);
	//Character.Animation2DPlayer.SetCurrentAnimationByID((int)AnimationIndex.IdleRight);
	FSM()->SetCurrentState(GetState((int)PlayerControllerState::IDLE));
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
	return Game::Instance()->GetInput().IsKeyJustDown(sf::Keyboard::Space);
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
	return Game::Instance()->GetInput().IsKeyJustDown(sf::Keyboard::Space);
}

/**
 * 
 */
Orientation PlayerController::GetDirectionFromInput(Vector2F& direction_)
{
	direction_ = Vector2F::Zero();

	// 	int mouseX = Game::Instance()->GetInput().GetMouseX();
	// 	int mouseY = Game::Instance()->GetInput().GetMouseY();
	// 	bool leftButton = Game::Instance()->GetInput().IsMouseButtonDown(sf::Mouse::Left);
	// 	bool rightButton = Game::Instance()->GetInput().IsMouseButtonDown(sf::Mouse::Right);
	// 	bool middleButton = Game::Instance()->GetInput().IsMouseButtonDown(sf::Mouse::Middle);
	// 
// 	if (Game::Instance()->GetInput().IsKeyDown(sf::Keyboard::Z) == true)
// 	{
// 		pPlayer_->SetCurrentAnimation("Anim_belrick_idle_u");
// 	}
// 	else if (Game::Instance()->GetInput().IsKeyDown(sf::Keyboard::S) == true)
// 	{
// 		pPlayer_->SetCurrentAnimation("Anim_belrick_idle_d");
// 	}
// 	else if (Game::Instance()->GetInput().IsKeyDown(sf::Keyboard::D) == true)
// 	{
// 		pPlayer_->SetCurrentAnimation("Anim_belrick_idle_r");
// 	}
// 	else if (Game::Instance()->GetInput().IsKeyDown(sf::Keyboard::Q) == true)
// 	{
// 		pPlayer_->SetCurrentAnimation("Anim_belrick_idle_l");
// 	}



	/*if (m_InputComponent.IsGamePadConnected(m_PlayerIndex) == true)
	{
		direction_ = m_InputComponent.GamePadState(m_PlayerIndex).ThumbSticks.Left;
	}
	else
	{*/
		if (Game::Instance()->GetInput().IsKeyDown(sf::Keyboard::Z) == true)
		{
			direction_.y = 1.0f;
		}
		else if (Game::Instance()->GetInput().IsKeyDown(sf::Keyboard::S) == true)
		{
			direction_.y = -1.0f;
		}

		if (Game::Instance()->GetInput().IsKeyDown(sf::Keyboard::D) == true)
		{
			direction_.x = -1.0f;
		}
		else if (Game::Instance()->GetInput().IsKeyDown(sf::Keyboard::Q) == true)
		{
			direction_.x = 1.0f;
		}
	//}

	if (direction_.x < -0.2f)
	{
		direction_.x = -1.0f;
	}
	else if (direction_.x > 0.2f)
	{
		direction_.x = 1.0f;
	}
	else
	{
		direction_.x = 0;
	}

	if (direction_.y < -0.2f)
	{
		direction_.y = -1.0f;
	}
	else if (direction_.y > 0.2f)
	{
		direction_.y = 1.0f;
	}
	else
	{
		direction_.y = 0;
	}

	if (direction_.x != 0.0f
		|| direction_.y != 0.0f)
	{
		direction_.Normalize();
	}

	Vector2F vec = direction_;
	vec.y = -vec.y; //inverse to be on screen coordinate
	return Character::GetOrientationFromVector2(vec);
}

/**
 * 
 */
Hero * PlayerController::GetHero() const
{
	return m_pHero;
}
