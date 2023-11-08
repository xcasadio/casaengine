#pragma once

#include <map>

#include  "GameTime.hpp"
#include  "AI/FSM/IState.hpp"
#include  "AI/FSM/StateMachine.hpp"

namespace CasaEngine
{
	class CharacterBase;

	class IController
	{
	public:
		virtual ~IController() = default;

		StateMachine<IController>* FSM();
		IState<IController>* GetState(int stateId);
		void AddState(int stateId, IState<IController>* state);
		virtual void Update(const GameTime& elapsedTime);
		CharacterBase* GetCharacter() const;

		virtual void Initialize() = 0;

	protected:
		IController(CharacterBase* pCharacter);

	private:
		StateMachine<IController> m_FSM;
		std::map<int, IState<IController>*> m_States;
		CharacterBase* m_pCharacter;
	};
}
