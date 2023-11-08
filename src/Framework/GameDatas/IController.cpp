#include  "Base.hpp"
#include  "IController.hpp"
#include  "Game/Game.hpp"
#include  "CA_Assert.hpp"

namespace CasaEngine
{
	IController::IController(CharacterBase* pCharacter) :
		m_FSM(this), m_pCharacter(pCharacter)
	{
		CA_ASSERT(m_pCharacter != nullptr, "IController() : Character is null")
	}

	IState<IController>* IController::GetState(int stateId)
	{
		return m_States[stateId];
	}

	void IController::AddState(int stateId, IState<IController>* state)
	{
		CA_ASSERT(m_States.find(stateId) == m_States.end(), "Controller::AddState() : the id %d already exist", stateId)

			m_States[stateId] = state;
	}

	void IController::Update(const GameTime& elapsedTime)
	{
		m_FSM.Update(elapsedTime);
	}

	StateMachine<IController>* IController::FSM()
	{
		return &m_FSM;
	}

	CharacterBase* IController::GetCharacter() const
	{
		return m_pCharacter;
	}
}