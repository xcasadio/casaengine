#include "Base.h"
#include "Character2DBase.h"
#include "CA_Assert.h"
#include "Log\LogManager.h"
#include "Assets\AssetManager.h"
#include "Entities\Physics\PhysicalEntity.h"
#include "AI\MovementSystem\MovementRequest.h"
#include "MessageType.h"
#include "Entities\Events\BaseEntityEvents.h"

namespace CasaEngine
{
	Character2DBase::Character2DBase(BaseEntity* pEntity) :
		CharacterBase(pEntity),
		m_NumberOfDirection(8),
		m_AnimationDirectionMask(0)
	{
		AnimatedSpriteComponent* pAnimatedSprite = pEntity->GetComponentMgr()->GetComponent<AnimatedSpriteComponent>();
		CA_ASSERT(pAnimatedSprite != nullptr, "Character2DBase() : AnimatedSpriteComponent is null");
		m_pAnimatedSprite = pAnimatedSprite;

		m_pAnimatedSprite->subscribeEvent(
			AnimationFinishedEvent::GetEventName(),
			Event::Subscriber(&Character2DBase::OnAnimationFinished, this));
		m_pAnimatedSprite->subscribeEvent(
			FrameChangeEvent::GetEventName(),
			Event::Subscriber(&Character2DBase::OnFrameChangedEvent, this));

		m_SpeedOffSet = 0.0f;
		m_Direction = Vector2::UnitX();
		m_Speed = 60.0f;
	}

	Character2DBase::~Character2DBase()
	{
	}

	void Character2DBase::Initialize()
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

	void Character2DBase::Update(const GameTime& gameTime_)
	{
		CharacterBase::Update(gameTime_);
	}

	void Character2DBase::Draw()
	{
		CharacterBase::Draw();
	}

	void Character2DBase::SetAnimationParameters(unsigned int numberOfDir_, unsigned int animationDirMask_)
	{
		m_NumberOfDirection = numberOfDir_;
		m_AnimationDirectionMask = animationDirMask_;
	}

	void Character2DBase::SetAnimationDirectionOffset(Orientation dir_, int offset_)
	{
		m_AnimationDirectionOffset[static_cast<int>(dir_)] = offset_;
	}

	Orientation Character2DBase::GetOrientationFromVector2(const Vector2 v)
	{
		unsigned int dir = 0;
		const float offset = 0.1f;

		if (v.x < -offset)
		{
			dir |= (int)Orientation::LEFT;
		}
		else if (v.x > offset)
		{
			dir |= (int)Orientation::RIGHT;
		}

		if (v.y < -offset)
		{
			dir |= (int)Orientation::UP;
		}
		else if (v.y > offset)
		{
			dir |= (int)Orientation::DOWN;
		}

		return static_cast<Orientation>(dir);
	}

	Orientation Character2DBase::GetOrientation() const
	{
		return m_Orientation;
	}

	void Character2DBase::SetOrientation(const Orientation val)
	{
		m_Orientation = val;
	}


	int Character2DBase::GetAnimationDirectionOffset()
	{
		return 0;
	}

	std::string Character2DBase::GetAnimationNameWithOrientation(const char* name, Orientation orientation)
	{
		std::ostringstream name_with_direction;
		name_with_direction << name;

		switch (orientation)
		{
		case Orientation::DOWN:
		case Orientation::DOWN_LEFT:
		case Orientation::DOWN_RIGHT:
			name_with_direction << "_down";
			break;

		case Orientation::RIGHT:
			name_with_direction << "_right";
			break;

		case Orientation::LEFT:
			name_with_direction << "_left";
			break;

		case Orientation::UP:
		case Orientation::UP_LEFT:
		case Orientation::UP_RIGHT:
			name_with_direction << "_up";
			break;
		}

		return name_with_direction.str();
	}


	float Character2DBase::Speed() const
	{
		return m_Speed;
	}

	void Character2DBase::Speed(float val)
	{
		m_Speed = val;
	}

	void Character2DBase::Move(Vector2& dir)
	{
		if (dir == Vector2::Zero())
		{
			//always when Vector2.Zero to stop movement
			//else if contact the Character2DBase will continue to move
			//m_Body.ResetDynamics();
			PhysicalEntity& physicalEntity = GetEntity()->GetPhysicalEntity();
			// 		MovementRequest request;
			// 		request.MoveType = STOP;
			// 		physicalEntity.MovementSystem.QueueRequest(request);
			physicalEntity.SetVelocity(Vector3::Zero());
		}
		else
		{
			Direction(dir);

			PhysicalEntity& physicalEntity = GetEntity()->GetPhysicalEntity();
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
			physicalEntity.SetVelocity(Vector3(dir.x, dir.y, 0.0f) * (m_Speed + m_SpeedOffSet));
			//physicalEntity->applyCentralImpulse(Vector3(dir_.x, dir_.y, 0.0f) * (m_Speed + m_SpeedOffSet));
		}
	}

	bool Character2DBase::SetCurrentAnimationByNameWithOrientation(const char* name)
	{
		std::string name_with_direction = GetAnimationNameWithOrientation(name, GetOrientation());
		return SetCurrentAnimationByName(name_with_direction.c_str());
	}

	bool Character2DBase::SetCurrentAnimationByName(const char* name) const
	{
		CA_ASSERT(m_pAnimatedSprite != nullptr, "Character2DBase::SetCurrentAnimation() : m_pAnimatedSprite == nullptr");
		CA_ASSERT(name != nullptr, "Character2DBase::SetCurrentAnimation() : animation name == nullptr");

		return m_pAnimatedSprite->SetCurrentAnimation(name);
	}

	bool Character2DBase::OnAnimationFinished(const EventArgs& e_)
	{
		const auto& event = static_cast<const AnimationFinishedEvent&>(e_);
		Telegram msg;
		msg.Sender = GetEntity()->Id();
		msg.Receiver = GetEntity()->Id();
		msg.Msg = (int)MessageType::ANIMATION_FINISHED;
		msg.ExtraInfo = &const_cast<AnimationFinishedEvent&>(event);
		QueueMessage(msg);

		return false;
	}

	bool Character2DBase::OnFrameChangedEvent(const EventArgs& e_)
	{
		const auto& event = static_cast<const AnimationFinishedEvent&>(e_);
		Telegram msg;
		msg.Sender = GetEntity()->Id();
		msg.Receiver = GetEntity()->Id();
		msg.Msg = (int)MessageType::FRAME_CHANGE_EVENT;
		msg.ExtraInfo = &const_cast<AnimationFinishedEvent&>(event);
		QueueMessage(msg);

		return false;
	}


	Vector2 Character2DBase::Direction() const
	{
		return m_Direction;
	}

	void Character2DBase::Direction(Vector2 val)
	{
		m_Direction = val;
	}
}