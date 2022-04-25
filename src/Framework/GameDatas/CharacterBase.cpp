#include "Base.h"
#include "CharacterBase.h"
#include "CA_Assert.h"
#include "Log\LogManager.h"
#include "Assets\AssetManager.h"
#include "Entities\Physics\PhysicalEntity.h"
#include "AI\MovementSystem\MovementRequest.h"

namespace CasaEngine
{
	CharacterBase::CharacterBase(BaseEntity* pEntity):
		m_Orientation()
	{
		AnimatedSpriteComponent* pAnimatedSprite = pEntity->GetComponentMgr()->GetComponent<AnimatedSpriteComponent>();

		CA_ASSERT(pAnimatedSprite != nullptr, "CharacterBase() : AnimatedSpriteComponent is null");
		m_pAnimatedSprite = pAnimatedSprite;

		m_pEntity = pEntity;

		m_pController = nullptr;

		m_SpeedOffSet = 0.0f;

		m_Direction = Vector2::UnitX();

		//TODO set after creation by the level configuration
		m_Speed = 30.0f;
	}

	void CharacterBase::QueueMessage(Telegram& msg)
	{
		m_MessageQueue.push(msg);
	}

	CharacterBase::~CharacterBase()
	{
		delete m_pController;
	}

	void CharacterBase::Initialize()
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

	void CharacterBase::Update(const GameTime& gameTime_)
	{
		while (m_MessageQueue.empty() == false)
		{
			HandleMessage(m_MessageQueue.front());
			m_MessageQueue.pop();
		}

		m_pController->Update(gameTime_);
	}

	void CharacterBase::Draw()
	{
	}

	bool CharacterBase::HandleMessage(const Telegram& msg)
	{
		return m_pController->FSM()->HandleMessage(msg);
	}

	orientation CharacterBase::GetOrientationFromVector2(const Vector2 v)
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

	orientation CharacterBase::GetOrientation() const
	{
		return m_Orientation;
	}

	void CharacterBase::SetController(IController* pController)
	{
		m_pController = pController;
	}

	void CharacterBase::SetOrientation(const orientation val)
	{
		m_Orientation = val;
	}

	IController* CharacterBase::GetController() const
	{
		return m_pController;
	}

	BaseEntity* CharacterBase::GetEntity()
	{
		return m_pEntity;
	}

	void CharacterBase::Move(Vector2& dir)
	{
		if (dir == Vector2::Zero())
		{
			//always when Vector2.Zero to stop movement
			//else if contact the CharacterBase will continue to move
			//m_Body.ResetDynamics();
			PhysicalEntity& physicalEntity = m_pEntity->GetPhysicalEntity();
			// 		MovementRequest request;
			// 		request.MoveType = STOP;
			// 		physicalEntity.MovementSystem.QueueRequest(request);
			physicalEntity.SetVelocity(Vector3::Zero());
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
			physicalEntity.SetVelocity(Vector3(dir.x, dir.y, 0.0f) * (m_Speed + m_SpeedOffSet));
			//physicalEntity->applyCentralImpulse(Vector3(dir_.x, dir_.y, 0.0f) * (m_Speed + m_SpeedOffSet));
		}
	}

	bool CharacterBase::SetCurrentAnimation(const char* name) const
	{
		CA_ASSERT(m_pAnimatedSprite != nullptr, "CharacterBase::SetCurrentAnimation() : m_pAnimatedSprite == nullptr");
		CA_ASSERT(name != nullptr, "CharacterBase::SetCurrentAnimation() : animation name == nullptr");

		return m_pAnimatedSprite->SetCurrentAnimation(name);
	}

	Vector2 CharacterBase::Direction() const
	{
		return m_Direction;
	}

	void CharacterBase::Direction(Vector2 val)
	{
		m_Direction = val;
	}

}