#ifndef ICONTROLLER_H_
#define ICONTROLLER_H_

#include "GameTime.h"
#include "AI\FSM\StateMachine.h"
#include "AI\FSM\IState.h"
#include <map>

class Character;
using namespace CasaEngine;


class IController
{
public:
	virtual ~IController();

	StateMachine<IController> *FSM();
	IState<IController> *GetState(int stateId_);
	void AddState(int stateId_, IState<IController> *pState_);
	virtual void Update(const GameTime elapsedTime_);
	Character* GetCharacter() const;
	
	virtual void Initialize() = 0;

protected:
	IController(Character *pCharacter);

private:
	StateMachine<IController> m_FSM;
	std::map<int, IState<IController> *> m_States;
	Character* m_pCharacter;
};

#endif
