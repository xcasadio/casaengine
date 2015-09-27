
#include "Entities/BaseEntity.h"

#include "MinerComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/ComponentTypeEnum.h"
#include <string>
#include "Game/Game.h"
#include "AI/FSM/StateMachine.h"
#include "MinerOwnedStates.h"
#include "Config.h"

using namespace CasaEngine;

/**
 * 
 */
MinerComponent::MinerComponent(BaseEntity* pEntity_) :
	Component(pEntity_, CUSTOM_COMPONENT + 1),
	m_Location(shack),
	m_iGoldCarried(0),
	m_iMoneyInBank(0),
	m_iThirst(0),
	m_iFatigue(0),
	m_Delay(0.0f)
{
	m_pStateMachine = ::new StateMachine<MinerComponent>(this);
	m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance());
	/* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
}

/**
 * 
 */
MinerComponent::~MinerComponent()
{
	delete m_pStateMachine;
}

/**
 * 
 */
StateMachine<MinerComponent>* MinerComponent::GetFSM() const
{ 
	return m_pStateMachine; 
}

/**
 * 
 */
void MinerComponent::Initialize()
{
	
}

/**
 * 
 */
void MinerComponent::Update(const GameTime& gameTime_)
{
	m_Delay += gameTime_.FrameTime();

	//used to create some latency between each update
	if (m_Delay >= updateDelay)
	{
		m_Delay -= updateDelay;
		m_iThirst += 1;
		m_pStateMachine->Update(gameTime_);
	}
}

/**
 * 
 */
bool MinerComponent::HandleMessage( const Telegram& msg )
{
	return m_pStateMachine->HandleMessage(msg);
}

/**
 * 
 */
void MinerComponent::AddToGoldCarried(const int val)
{
	m_iGoldCarried += val;

	if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}

void MinerComponent::AddToWealth(const int val)
{
	m_iMoneyInBank += val;

	if (m_iMoneyInBank < 0) m_iMoneyInBank = 0;
}

bool MinerComponent::Thirsty()const
{
	if (m_iThirst >= ThirstLevel){return true;}

	return false;
}

bool MinerComponent::Fatigued()const
{
	if (m_iFatigue > TirednessThreshold)
	{
		return true;
	}

	return false;
}

/**
 * 
 */
/*void MinerComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
void MinerComponent::Write(std::ostream&  os) const
{

}

/**
 * 
 */
void MinerComponent::Read (std::ifstream& is)
{

}

