#include "Base.h"
#include "Character.h"
#include "CharacterEnum.h"
#include "CA_Assert.h"
#include "PlayerController.h"
#include "Log\LogManager.h"
#include "Entities\Events\BaseEntityEvents.h"
#include "EventHandler\Event.h"
#include "Assets\AssetManager.h"
#include "Entities\Physics\PhysicalEntity.h"
#include "AI\MovementSystem\MovementRequest.h"
#include "Entities\Events\BaseEntityEvents.h"
#include "EventHandler\Event.h"
#include "GameDatas/MessageType.h"


Character::Character(BaseEntity* pEntity) :
	CharacterBase(pEntity),
	m_HPMax(100),
	m_HPMaxOffSet(0.0f),
	m_HPOffSet(0.0f),
	m_MPMax(100),
	m_MPMaxOffSet(0.0f),
	m_MPOffSet(0.0f),
	m_Strength(10),
	m_StrengthOffSet(0.0f),
	m_DefenseOffSet(0.0f),
	m_NumberOfDirection(8),
	m_AnimationDirectionMask(0)
	//m_pLastSprite(nullptr)
{
	m_pAnimatedSprite->subscribeEvent(
		AnimationFinishedEvent::GetEventName(),
		Event::Subscriber(&Character::OnAnimationFinished, this));
	m_pAnimatedSprite->subscribeEvent(
		FrameChangeEvent::GetEventName(),
		Event::Subscriber(&Character::OnFrameChangedEvent, this));

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

Character::~Character() = default;

void Character::Initialize()
{
	CharacterBase::Initialize();

	m_HP = m_HPMax;
	m_MP = m_MPMax;

	m_HPMaxOffSet = 0;
	m_HPOffSet = 0;
	m_MPMaxOffSet = 0;
	m_MPOffSet = 0;
	m_StrengthOffSet = 0;
	m_DefenseOffSet = 0;
	m_ComboNumber = 0;
	m_IsPlayer = false;


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
}

void Character::Update(const GameTime& gameTime_)
{
	CharacterBase::Update(gameTime_);
}

void Character::Draw()
{
}

bool Character::HandleMessage(const Telegram& msg)
{
	if (msg.ExtraInfo != nullptr && msg.Msg == (int)MessageType::COLLISION)
	{
		if (this->GetEntity()->Id() == msg.Sender || this->GetEntity()->Id() == msg.Receiver)
		{
			
		}
	}

	return CharacterBase::HandleMessage(msg);
}

void Character::SetAnimationParameters(unsigned int numberOfDir_, unsigned int animationDirMask_)
{
	m_NumberOfDirection = numberOfDir_;
	m_AnimationDirectionMask = animationDirMask_;
}

void Character::SetAnimationDirectionOffset(orientation dir_, int offset_)
{
	m_AnimationDirectionOffset[static_cast<int>(dir_)] = offset_;
}

bool Character::IsDead() const
{
	return m_HP <= 0;
}

int Character::GetAnimationDirectionOffset()
{
	return 0;
}

std::string Character::GetAnimationNameWithOrientation(const char* name, orientation orientation)
{
	std::ostringstream name_with_direction;
	name_with_direction << name;

	switch (orientation)
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

	return name_with_direction.str();
}

bool Character::SetCurrentAnimationByName(const char* name)
{
	std::string name_with_direction = GetAnimationNameWithOrientation(name, GetOrientation());
	return SetCurrentAnimation(name_with_direction.c_str());
}


bool Character::OnAnimationFinished(const EventArgs& e_)
{
	const auto& event = static_cast<const AnimationFinishedEvent&>(e_);

	//event.ID();
	Telegram msg;
	msg.Msg = (int)MessageType::ANIMATION_FINISHED;
	msg.ExtraInfo = &event;
	QueueMessage(msg);

	return false;
}

bool Character::OnFrameChangedEvent(const EventArgs& e_)
{
	const auto& event = static_cast<const AnimationFinishedEvent&>(e_);

	//event.ID();
	Telegram msg;
	msg.Msg = (int)MessageType::FRAME_CHANGE_EVENT;
	msg.ExtraInfo = &event;
	QueueMessage(msg);

	//PhysicalEntity& physicalEntity = m_pEntity->GetPhysicalEntity();
	//Sprite* pNewSprite = new Sprite(*Game::Instance().GetAssetManager().GetAsset<SpriteData>(event.ID()));

	//physicalEntity.AddSpritePhysics(pNewSprite);

	return false;
}
