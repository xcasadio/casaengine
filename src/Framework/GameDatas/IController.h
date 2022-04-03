#ifndef ICONTROLLER_H_
#define ICONTROLLER_H_

#include <map>

#include "GameTime.h"
#include "AI\FSM\IState.h"
#include "AI\FSM\StateMachine.h"

namespace CasaEngine
{
	class CharacterBase;

	class IController : public AllocatedObject<IController>
	{
	public:
		StateMachine<IController>* FSM();
		IState<IController>* GetState(int stateId_);
		void AddState(int stateId_, IState<IController>* pState_);
		virtual void Update(const GameTime elapsedTime_);
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
	
#endif
