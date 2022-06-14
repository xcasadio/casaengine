#include "Base.h"
#include "CharacterBase.h"
#include "MessageType.h"
#include "Game/Game.h"

namespace CasaEngine
{
	CharacterBase::CharacterBase(BaseEntity* pEntity)
	{
		m_pEntity = pEntity;
		m_pController = nullptr;
		m_IsPlayer = false;
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
		if (msg.ExtraInfo != nullptr
			&& msg.Msg == (int)MessageType::COLLISION
			&& (GetEntity()->Id() == msg.Sender || GetEntity()->Id() == msg.Receiver)
			&& msg.Sender != msg.Receiver)
		{
			auto* otherEntity = GetEntity()->Id() == msg.Sender ? Game::Instance().GetEntityManager().GetEntityFromId(msg.Receiver) : Game::Instance().GetEntityManager().GetEntityFromId(msg.Sender);
			auto* collisionParameters = static_cast<CollisionParametersBetween2Entities*>(msg.ExtraInfo);

			CollideWith(
				collisionParameters->CollisionParameters1()->GetEntity()->Id() == GetEntity()->Id() ? collisionParameters->CollisionParameters1() : collisionParameters->CollisionParameters2(),
				otherEntity,
				collisionParameters->CollisionParameters1()->GetEntity()->Id() == otherEntity->Id() ? collisionParameters->CollisionParameters1() : collisionParameters->CollisionParameters2());
		}
		
		return m_pController->FSM()->HandleMessage(msg);
	}

	void CharacterBase::SetController(IController* pController)
	{
		m_pController = pController;
	}

	IController* CharacterBase::GetController() const
	{
		return m_pController;
	}

	BaseEntity* CharacterBase::GetEntity()
	{
		return m_pEntity;
	}
}
