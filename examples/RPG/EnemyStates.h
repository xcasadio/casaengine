#ifndef ENEMYSTATES_H_
#define ENEMYSTATES_H_

#include "GameTime.h"
#include "AI\FSM\IState.h"
#include "IController.h"

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

	void Enter(IController *pController_) override;
	void Execute(IController *pController_, GameTime elpasedTime_);
	void Exit(IController *pController_) override;
	bool OnMessage(IController *pController_, const Telegram& msg) override;

private:

};

#endif // ENEMYSTATES_H_