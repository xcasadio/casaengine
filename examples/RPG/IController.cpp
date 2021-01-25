#include "Base.h"
#include "IController.h"
#include "Game\Game.h"
#include "CA_Assert.h"

/**
 *
 */
IController::IController(Character* pCharacter) :
	m_FSM(this), m_pCharacter(pCharacter)
{
	CA_ASSERT(m_pCharacter != nullptr, ":IController() : Character is null");
}

/**
 *
 */
IController::~IController()
{
}

/**
 *
 */
IState<IController>* IController::GetState(int stateId_)
{
	return m_States[stateId_];
}

/**
 *
 */
void IController::AddState(int stateId_, IState<IController>* pState_)
{
	CA_ASSERT(m_States.find(stateId_) == m_States.end(), "Controller::AddState() : the id %d already exist", stateId_);

	m_States[stateId_] = pState_;
}

/**
 *
 */
void IController::Update(const GameTime elapsedTime_)
{
	m_FSM.Update(elapsedTime_);
}

/**
 *
 */
StateMachine<IController>* IController::FSM()
{
	return &m_FSM;
}

/**
 *
 */
Character* IController::GetCharacter() const
{
	return m_pCharacter;
}