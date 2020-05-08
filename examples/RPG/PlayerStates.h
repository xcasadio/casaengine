#ifndef PLAYERSTATES_H_
#define PLAYERSTATES_H_


#include "GameTime.h"
#include "AI\FSM\IState.h"
#include "IController.h"


using namespace CasaEngine;

class ScriptPlayer;

enum PlayerControllerState
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
	TO_FURY_MODE,
	TO_NORMAL_MODE,
};

//////////////////////////////////////////////////////////////////////////

/**
 * 
 */
class PlayerStateIdle : 
	public IState<IController>
{
public:
	PlayerStateIdle();
	~PlayerStateIdle();

	void Enter(IController *pController_) override;
	void Execute(IController *pController_, const GameTime &elpasedTime_) override;
	void Exit(IController *pController_) override;
	bool OnMessage(IController *pController_, const Telegram& msg) override;

private:

};

//////////////////////////////////////////////////////////////////////////

/**
 * 
 */
class PlayerStateAttack : 
	public IState<IController>
{
public:
	PlayerStateAttack();
	~PlayerStateAttack();

	void Enter(IController *pController_) override;
	void Execute(IController *pController_, const GameTime &elpasedTime_) override;
	void Exit(IController *pController_) override;
	bool OnMessage(IController *pController_, const Telegram& msg) override;

private:

};



#endif // PLAYERSTATES_H_