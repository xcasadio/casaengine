#include "Base.h"
#include "CharacterBase.h"
#include "CA_Assert.h"
#include "Log\LogManager.h"
#include "Assets\AssetManager.h"
#include "Entities\Physics\PhysicalEntity.h"
#include "AI\MovementSystem\MovementRequest.h"
#include "MessageType.h"

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
		if (msg.ExtraInfo != nullptr && msg.Msg == (int)MessageType::COLLISION)
		{
			if ((GetEntity()->Id() == msg.Sender || GetEntity()->Id() == msg.Receiver)
				&& msg.Sender != msg.Receiver)
			{
				auto* otherEntity = GetEntity()->Id() == msg.Sender ? Game::Instance().GetEntityManager().GetEntityFromID(msg.Receiver) : Game::Instance().GetEntityManager().GetEntityFromID(msg.Sender);
				CollideWith(otherEntity, static_cast<CollisionParametersBetween2Entities*>(msg.ExtraInfo));
			}
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