#include "Base.h"
#include "Character.h"
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


Character::Character(BaseEntity* pEntity) : CasaEngine::CharacterBase(pEntity)
{
	m_pAnimatedSprite->subscribeEvent(
		AnimationFinishedEvent::GetEventName(),
		Event::Subscriber(&Character::OnAnimationFinished, this));
	m_pAnimatedSprite->subscribeEvent(
		FrameChangeEvent::GetEventName(),
		Event::Subscriber(&Character::OnFrameChangedEvent, this));

	m_HPMax = 100;
	m_MPMax = 100;
	m_Speed = 30.0f;
}

Character::~Character()
{
}

void Character::Initialize()
{
	CharacterBase::Initialize();
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

bool Character::SetCurrentAnimationByName(const char* name)
{
	/*std::ostringstream name_with_direction;
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
	}*/

	return SetCurrentAnimation(name);
}


bool Character::OnAnimationFinished(const EventArgs& e_)
{
	const auto& event = static_cast<const AnimationFinishedEvent&>(e_);

	//event.Id();
	Telegram msg;
	msg.Sender = GetEntity()->Id();
	msg.Receiver = GetEntity()->Id();
	//msg.Msg = ANIMATION_FINISHED;
	msg.ExtraInfo = &event;
	QueueMessage(msg);

	return false;
}

bool Character::OnFrameChangedEvent(const EventArgs& e_)
{
	const auto& event = static_cast<const AnimationFinishedEvent&>(e_);

	//event.ID();
	Telegram msg;
	msg.Sender = GetEntity()->Id();
	msg.Receiver = GetEntity()->Id();
	msg.Msg = static_cast<int>(MessageType::FRAME_CHANGE_EVENT);
	msg.ExtraInfo = &event;
	QueueMessage(msg);

	//PhysicalEntity& physicalEntity = m_pEntity->GetPhysicalEntity();
	//Sprite* pNewSprite = new Sprite(*Game::Instance().GetAssetManager().GetAsset<SpriteData>(event.ID()));

	//physicalEntity.AddSpritePhysics(pNewSprite);

	return false;
}
