#include "Base.h"
#include "Character.h"
#include "CharacterEnum.h"
#include "CustomComponentType.h"
#include "CA_Assert.h"
#include "PlayerController.h"
#include "Log\LogManager.h"
#include "Entities\Events\BaseEntityEvents.h"
#include "EventHandler\Event.h"
#include "MessageType.h"
#include "Assets\AssetManager.h"
#include "Entities\Physics\PhysicalEntity.h"
#include "AI\MovementSystem\MovementRequest.h"

/**
 *
 */
Character::Character(BaseEntity* pEntity)
{
	AnimatedSpriteComponent* pAnimatedSprite = pEntity->GetComponentMgr()->GetComponent<AnimatedSpriteComponent>();
	
	CA_ASSERT(pAnimatedSprite != nullptr, "Character() : AnimatedSpriteComponent is null");
	m_pAnimatedSprite = pAnimatedSprite;

	m_pEntity = pEntity;

	m_pAnimatedSprite->subscribeEvent(
		AnimationFinishedEvent::GetEventName(),
		Event::Subscriber(&Character::OnAnimationFinished, this));
	m_pAnimatedSprite->subscribeEvent(
		FrameChangeEvent::GetEventName(),
		Event::Subscriber(&Character::OnFrameChangedEvent, this));

	m_pLastSprite = nullptr;
	m_pController = nullptr;

	m_NumberOfDirection = 8;
	m_AnimationDirectioMask = 0;

	m_Speed = 2.0f;
	m_Strength = 10;
	m_HPMax = 100;
	m_MPMax = 100;

	m_SpeedOffSet = 0.0f;
	int m_HPMaxOffSet = 0.0f;
	int m_HPOffSet = 0.0f;
	int m_MPMaxOffSet = 0.0f;
	int m_MPOffSet = 0.0f;
	int m_StrengthOffSet = 0.0f;
	int m_DefenseOffSet = 0.0f;

	m_Direction = Vector2F::UnitX();
	//m_Velocity = Vector2F::Zero();

	SetAnimationDirectionOffset(orientation::DOWN, (int)AnimationDirectionOffset::DOWN);
	SetAnimationDirectionOffset(orientation::DOWN_LEFT, (int)AnimationDirectionOffset::DOWN_LEFT);
	SetAnimationDirectionOffset(orientation::DOWN_RIGHT, (int)AnimationDirectionOffset::DOWN_RIGHT);
	SetAnimationDirectionOffset(orientation::RIGHT, (int)AnimationDirectionOffset::RIGHT);
	SetAnimationDirectionOffset(orientation::LEFT, (int)AnimationDirectionOffset::LEFT);
	SetAnimationDirectionOffset(orientation::UP, (int)AnimationDirectionOffset::UP);
	SetAnimationDirectionOffset(orientation::UP_LEFT, (int)AnimationDirectionOffset::UP_LEFT);
	SetAnimationDirectionOffset(orientation::UP_RIGHT, (int)AnimationDirectionOffset::UP_RIGHT);
	SetAnimationParameters(4, -1);
}

/**
 *
 */
Character::~Character()
{
	DELETE_AO m_pController;
}

/**
 *
 */
void Character::Initialize()
{
	/*foreach (KeyValuePair<int, Animation2D> pair in m_Animations)
	{
		//Event
		pair.Value.InitializeEvent();

		//sprite
		GameInfo.Instance.Asset2DManager.AddSprite2DToLoadingList(pair.Value);
	}

	InitializePhysics(physicWorld_);

	Collision2DManager.Instance.RegisterObject(this);

	m_ShapeRendererComponent = GameHelper.GetDrawableGameComponent<ShapeRendererComponent>(GameInfo.Instance.Game);

	HP = HPMax;
	MP = MPMax;*/

	m_pController->Initialize();
}

/**
 *
 */
void Character::Update(const GameTime& gameTime_)
{
	while (m_MessageQueue.empty() == false)
	{
		HandleMessage(m_MessageQueue.front());
		m_MessageQueue.pop();
	}

	m_pController->Update(gameTime_);
}

/**
 *
 */
void Character::Draw()
{

}

/**
 *
 */
void Character::SetAnimationParameters(unsigned int numberOfDir_, unsigned int animationDirMask_)
{
	m_NumberOfDirection = numberOfDir_;
	m_AnimationDirectioMask = animationDirMask_;
}

/**
 *
 */
void Character::SetAnimationDirectionOffset(orientation dir_, int offset_)
{
	m_AnimationDirectionOffset[(int)dir_] = offset_;
}

/**
 *
 */
bool Character::HandleMessage(const Telegram& msg)
{
	return m_pController->FSM()->HandleMessage(msg);
}


/**
 *
 */
orientation Character::GetOrientationFromVector2(Vector2F v_)
{
	unsigned int dir = 0;

	if (v_.x < -Deadzone)
	{
		dir |= orientation::RIGHT;
	}
	else if (v_.x > Deadzone)
	{
		dir |= orientation::LEFT;
	}

	if (v_.y < -Deadzone)
	{
		dir |= orientation::UP;
	}
	else if (v_.y > Deadzone)
	{
		dir |= orientation::DOWN;
	}

	return static_cast<orientation>(dir);
}

/**
 *
 */
orientation Character::GetOrientation() const
{
	return m_Orientation;
}

/**
 *
 */
void Character::SetOrientation(orientation val)
{
	m_Orientation = val;
}

/**
 *
 */
IController* Character::GetController() const
{
	return m_pController;
}

/**
 *
 */
void Character::Move(Vector2F& dir_)
{
	if (dir_ == Vector2F::Zero())
	{
		//always when Vector2.Zero to stop movement
		//else if contact the character will continue to move
		//m_Body.ResetDynamics();
		PhysicalEntity& physicalEntity = m_pEntity->GetPhysicalEntity();
		// 		MovementRequest request;
		// 		request.MoveType = STOP;
		// 		physicalEntity.MovementSystem.QueueRequest(request);
		physicalEntity.SetVelocity(Vector3F::Zero());
	}
	else
	{
		Direction(dir_);

		PhysicalEntity& physicalEntity = m_pEntity->GetPhysicalEntity();
		// 		physicalEntity.MoveRequest(MOVE, dir_, m_Speed + m_SpeedOffSet);
		// 
		// 		MovementStyle mvtStyle;
		// 		mvtStyle.Stance = STAND;
		// 		mvtStyle.Speed = Run;
		// 
		// 
		// 		MovementRequest request;
		// 		request.MoveType = MOVETO;
		// 		request.Destination = pos + dir_ * 10.0f;
		// 		request.Velocity = m_Speed + m_SpeedOffSet;
		// 		request.Style = mvtStyle;
		// 		physicalEntity.MovementSystem.QueueRequest(request);
		physicalEntity.SetVelocity(Vector3F(dir_.x, dir_.y, 0.0f) * (m_Speed + m_SpeedOffSet));
		//physicalEntity->applyCentralImpulse(Vector3F(dir_.x, dir_.y, 0.0f) * (m_Speed + m_SpeedOffSet));
	}
}

/**
 *
 */
int Character::GetAnimationDirectionOffset()
{
	int val = (int)m_Orientation & m_AnimationDirectioMask;
	return m_AnimationDirectionOffset[(int)m_Orientation & m_AnimationDirectioMask];
}

/**
 *
 */
void Character::SetCurrentAnimation(int index_)
{
	CA_ASSERT(m_pAnimatedSprite != nullptr, "Character::SetCurrentAnimation() : m_pAnimatedSprite == nullptr");

	m_pAnimatedSprite->SetCurrentAnimation(index_ * m_NumberOfDirection + GetAnimationDirectionOffset());
}

/**
 *
 */
void Character::SetCurrentAnimation(const char* name_)
{
	CA_ASSERT(m_pAnimatedSprite != nullptr, "Character::SetCurrentAnimation() : m_pAnimatedSprite == nullptr");
	CA_ASSERT(name_ != nullptr, "Character::SetCurrentAnimation() : animation name == nullptr");

	m_pAnimatedSprite->SetCurrentAnimation(name_);
}

/**
 *
 */
Vector2F Character::Direction() const
{
	return m_Direction;
}

/**
 *
 */
void Character::Direction(Vector2F val)
{
	m_Direction = val;
}

/**
 *
 */
bool Character::OnAnimationFinished(const EventArgs& e_)
{
	const AnimationFinishedEvent& event = static_cast<const AnimationFinishedEvent&>(e_);

	//event.ID();
	Telegram msg;
	msg.Msg = MessageType::ANIMATION_FINISHED;
	msg.ExtraInfo = &event;
	m_MessageQueue.push(msg);

	return false;
}

/**
 *
 */
bool Character::OnFrameChangedEvent(const EventArgs& e_)
{
	const AnimationFinishedEvent& event = static_cast<const AnimationFinishedEvent&>(e_);

	//event.ID();
	Telegram msg;
	msg.Msg = MessageType::FRAME_CHANGE_EVENT;
	msg.ExtraInfo = &event;
	m_MessageQueue.push(msg);

	PhysicalEntity& physicalEntity = m_pEntity->GetPhysicalEntity();
	Sprite* pNewSprite = Game::Instance().GetAssetManager().GetAsset<Sprite>(event.ID());

	if (m_pLastSprite != nullptr)
	{
		physicalEntity.RemoveSpritePhysics(m_pLastSprite);
	}

	physicalEntity.AddSpritePhysics(pNewSprite);
	m_pLastSprite = pNewSprite;

	return false;
}
