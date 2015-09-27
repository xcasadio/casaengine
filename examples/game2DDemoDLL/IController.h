#ifndef ICONTROLLER_H_
#define ICONTROLLER_H_

#include "GameTime.h"
#include "Export.h"
#include "AI\FSM\StateMachine.h"
#include "AI\FSM\IState.h"
#include <map>


using namespace CasaEngine;

/**
 * 
 */
class IController
{
public:
	IController();
	virtual ~IController();

	StateMachine<IController> *FSM();
	IState<IController> *GetState(int stateId_);
	void AddState(int stateId_, IState<IController> *pState_);
	virtual void Update(const GameTime elapsedTime_);
	
	virtual void Initialize() = 0;

private:
	StateMachine<IController> m_FSM;
	std::map<int, IState<IController> *> m_States;
};

#endif // ICONTROLLER_H_