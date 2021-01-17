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

	m_SpeedOffSet = 0.0f;
	int m_HPMaxOffSet = 0.0f;
	int m_HPOffSet = 0.0f;
	int m_MPMaxOffSet = 0.0f;
	int m_MPOffSet = 0.0f;
	int m_StrengthOffSet = 0.0f;
	int m_DefenseOffSet = 0.0f;

	m_Direction = Vector2F::UnitX();
	//m_Velocity = Vector2F::Zero();

	//TODO set after creation by the level configuration
	m_Speed = 20.0f;
	m_Strength = 10;
	m_HPMax = 100;
	m_MPMax = 100;

	SetAnimationDirectionOffset(DOWN, static_cast<int>(AnimationDirectionOffset::DOWN));
	//SetAnimationDirectionOffset(DOWN_LEFT, static_cast<int>(AnimationDirectionOffset::DOWN_LEFT));
	//SetAnimationDirectionOffset(DOWN_RIGHT, static_cast<int>(AnimationDirectionOffset::DOWN_RIGHT));
	SetAnimationDirectionOffset(RIGHT, static_cast<int>(AnimationDirectionOffset::RIGHT));
	SetAnimationDirectionOffset(LEFT, static_cast<int>(AnimationDirectionOffset::LEFT));
	SetAnimationDirectionOffset(UP, static_cast<int>(AnimationDirectionOffset::UP));
	//SetAnimationDirectionOffset(UP_LEFT, static_cast<int>(AnimationDirectionOffset::UP_LEFT));
	//SetAnimationDirectionOffset(UP_RIGHT, static_cast<int>(AnimationDirectionOffset::UP_RIGHT));
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
	m_AnimationDirectionOffset[static_cast<int>(dir_)] = offset_;
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
orientation Character::GetOrientationFromVector2(const Vector2F v)
{
	unsigned int dir = 0;
	const float offset = 0.1f;

	if (v.x < -offset)
	{
		dir |= LEFT;
	}
	else if (v.x > offset)
	{
		dir |= RIGHT;
	}

	if (v.y < -offset)
	{
		dir |= UP;
	}
	else if (v.y > offset)
	{
		dir |= DOWN;
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
void Character::SetOrientation(const orientation val)
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
void Character::Move(Vector2F& dir)
{
	if (dir == Vector2F::Zero())
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
		Direction(dir);

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
		physicalEntity.SetVelocity(Vector3F(dir.x, dir.y, 0.0f) * (m_Speed + m_SpeedOffSet));
		//physicalEntity->applyCentralImpulse(Vector3F(dir_.x, dir_.y, 0.0f) * (m_Speed + m_SpeedOffSet));
	}
}

/**
 *
 */
int Character::GetAnimationDirectionOffset()
{
	//int val = static_cast<int>(m_Orientation) & m_AnimationDirectioMask;
	return m_AnimationDirectionOffset[static_cast<int>(m_Orientation) & m_AnimationDirectioMask];
}

/**
 *
 */
void Character::SetCurrentAnimation(int index_)
{
	CA_ASSERT(m_pAnimatedSprite != nullptr, "Character::SetCurrentAnimation() : m_pAnimatedSprite == nullptr");

	m_pAnimatedSprite->SetCurrentAnimation(index_ * m_NumberOfDirection + GetAnimationDirectionOffset());
}

//AnimationDirectionOffset::RIGHT
void Character::SetCurrentAnimationByName(const char* name)
{
	CA_ASSERT(m_pAnimatedSprite != nullptr, "Character::SetCurrentAnimation() : m_pAnimatedSprite == nullptr");
	std::ostringstream name_with_direction;
	name_with_direction << name;

	switch (GetOrientation())
	{
	case orientation::DOWN:
	case orientation::DOWN_LEFT:
	case orientation::DOWN_RIGHT:
		name_with_direction << "_down";
		break;

	case orientation::RIGHT:
		name_with_direction << "_right";
		break;

	case orientation::LEFT:
		name_with_direction << "_left";
		break;

	case orientation::UP:
	case orientation::UP_LEFT:
	case orientation::UP_RIGHT:
		name_with_direction << "_up";
		break;
	}

	m_pAnimatedSprite->SetCurrentAnimation(name_with_direction.str());
}

/**
 *
 */
void Character::SetCurrentAnimation(const char* name) const
{
	CA_ASSERT(m_pAnimatedSprite != nullptr, "Character::SetCurrentAnimation() : m_pAnimatedSprite == nullptr");
	CA_ASSERT(name != nullptr, "Character::SetCurrentAnimation() : animation name == nullptr");

	m_pAnimatedSprite->SetCurrentAnimation(name);
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
	msg.Msg = ANIMATION_FINISHED;
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
	msg.Msg = FRAME_CHANGE_EVENT;
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
