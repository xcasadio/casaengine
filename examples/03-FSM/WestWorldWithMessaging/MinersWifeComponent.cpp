#include "Entities/BaseEntity.h"

#include "MinersWifeComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"
#include "AI/FSM/StateMachine.h"
#include "MinersWifeOwnedStates.h"
#include "Config.h"

using namespace CasaEngine;

/**
 *
 */
MinersWifeComponent::MinersWifeComponent(BaseEntity* pEntity_) :
	Component(pEntity_, CUSTOM_COMPONENT + 2),
	m_Location(shack),
	m_bCooking(false),
	m_Delay(0.0f)
{
	m_pStateMachine = ::new StateMachine<MinersWifeComponent>(this);
	m_pStateMachine->SetCurrentState(DoHouseWork::Instance());
	m_pStateMachine->SetGlobalState(WifesGlobalState::Instance());
}

/**
 *
 */
MinersWifeComponent::~MinersWifeComponent()
{
	delete m_pStateMachine;
}

/**
 *
 */
StateMachine<MinersWifeComponent>* MinersWifeComponent::GetFSM() const
{
	return m_pStateMachine;
}

/**
 *
 */
void MinersWifeComponent::Initialize()
{
}

/**
 *
 */
void MinersWifeComponent::Update(const GameTime& gameTime_)
{
	m_Delay += gameTime_.FrameTime();

	//used to create some latency between each update
	if (m_Delay >= updateDelay)
	{
		m_Delay -= updateDelay;
		m_pStateMachine->Update(gameTime_);
	}
}

/**
 *
 */
bool MinersWifeComponent::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

/**
 *
 */
 /*void MinersWifeComponent::HandleEvent(const Event* pEvent_)
 {
 }*/

 /**
  *
  */
void MinersWifeComponent::Write(std::ostream& os) const
{
}

/**
 *
 */
void MinersWifeComponent::Read(std::ifstream& is)
{
}