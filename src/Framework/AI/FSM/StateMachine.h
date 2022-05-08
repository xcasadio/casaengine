#pragma once

#include "IState.h"
#include "Messaging/Telegram.h"
#include "Log/LogManager.h"

#include <string>

#include <typeinfo>
#include "CA_Assert.h"
#include "GameTime.h"

namespace CasaEngine
{
	template <class entity_type>
	class StateMachine
	{
	private:
		entity_type* m_pOwner;
		IState<entity_type>* m_pCurrentState;
		IState<entity_type>* m_pPreviousState;
		IState<entity_type>* m_pGlobalState; //this is called every time the FSM is updated

	public:
		StateMachine(entity_type* owner);
		virtual ~StateMachine();

		void SetCurrentState(IState<entity_type>* s);
		void SetGlobalState(IState<entity_type>* s);
		void SetPreviousState(IState<entity_type>* s);

		void Update(const GameTime& elapsedTime_) const;

		bool  HandleMessage(const Telegram& msg) const;

		void  ChangeState(IState<entity_type>* pNewState);
		void  RevertToPreviousState();
		bool  isInState(const IState<entity_type>& st) const;

		IState<entity_type>* CurrentState()  const;
		IState<entity_type>* GlobalState()   const;
		IState<entity_type>* PreviousState() const;

		std::string GetNameOfCurrentState() const; //only ever used during debugging to grab the name of the current state
	};

	template <class entity_type>
	StateMachine<entity_type>::StateMachine(entity_type* owner) :
		m_pOwner(owner),
		m_pCurrentState(nullptr),
		m_pPreviousState(nullptr),
		m_pGlobalState(nullptr)
	{}

	template <class entity_type>
	StateMachine<entity_type>::~StateMachine() = default;

	template <class entity_type>
	void StateMachine<entity_type>::SetPreviousState(IState<entity_type>* s)
	{
		m_pPreviousState = s;
	}

	template <class entity_type>
	void StateMachine<entity_type>::Update(const GameTime& elapsedTime_) const
	{
		if (m_pGlobalState)
		{
			m_pGlobalState->Execute(m_pOwner, elapsedTime_);
		}

		if (m_pCurrentState)
		{
			m_pCurrentState->Execute(m_pOwner, elapsedTime_);
		}
	}

	template <class entity_type>
	bool StateMachine<entity_type>::HandleMessage(const Telegram& msg) const
	{
		if (m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg))
		{
			return true;
		}

		if (m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, msg))
		{
			return true;
		}

		return false;
	}

	template <class entity_type>
	void StateMachine<entity_type>::ChangeState(IState<entity_type>* pNewState)
	{
		CA_ASSERT(pNewState != nullptr, "<StateMachine<entity_type>::ChangeState>:trying to assign null state to current");
		m_pPreviousState = m_pCurrentState;

		if (m_pCurrentState != nullptr)
		{
			m_pCurrentState->Exit(m_pOwner);
		}

		m_pCurrentState = pNewState;
		m_pCurrentState->Enter(m_pOwner);
	}

	template <class entity_type>
	void StateMachine<entity_type>::RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	template <class entity_type>
	bool StateMachine<entity_type>::isInState(const IState<entity_type>& st) const
	{
		if (typeid(*m_pCurrentState) == typeid(st))
		{
			return true;
		}
		return false;
	}

	template <class entity_type>
	IState<entity_type>* StateMachine<entity_type>::CurrentState() const
	{
		return m_pCurrentState;
	}

	template <class entity_type>
	IState<entity_type>* StateMachine<entity_type>::GlobalState() const
	{
		return m_pGlobalState;
	}

	template <class entity_type>
	IState<entity_type>* StateMachine<entity_type>::PreviousState() const
	{
		return m_pPreviousState;
	}

	template <class entity_type>
	std::string StateMachine<entity_type>::GetNameOfCurrentState() const
	{
		std::string s(typeid(*m_pCurrentState).name());

		//remove the 'class ' part from the front of the string
		if (s.size() > 5)
		{
			s.erase(0, 6);
		}

		return s;
	}

	template <class entity_type>
	void StateMachine<entity_type>::SetCurrentState(IState<entity_type>* s)
	{
		m_pCurrentState = s;
	}

	template <class entity_type>
	void StateMachine<entity_type>::SetGlobalState(IState<entity_type>* s)
	{
		m_pGlobalState = s;
	}
}
