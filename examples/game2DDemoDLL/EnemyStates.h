#ifndef ENEMYSTATES_H_
#define ENEMYSTATES_H_


#include "GameTime.h"
#include "Export.h"
#include "AI\FSM\IState.h"
#include "IController.h"
#include "CompilationMacro.h"

using namespace CasaEngine;

/**
 * 
 */
enum EnemyControllerState
{
	IDLE,
	MOVING,
	ATTACK_1,
	ATTACK_2,
	ATTACK_3,
	MAGIC_1,
	MAGIC_2,
	HIT,
	DEAD,
};


/**
 * 
 */
class EnemyStateIdle : 
	public IState<IController>
{
public:
	EnemyStateIdle();
	~EnemyStateIdle();

	void Enter(IController *pController_) OVERRIDE;
	void Execute(IController *pController_, GameTime elpasedTime_) OVERRIDE;
	void Exit(IController *pController_) OVERRIDE;
	bool OnMessage(IController *pController_, const Telegram& msg) OVERRIDE;

private:

};

#endif // ENEMYSTATES_H_