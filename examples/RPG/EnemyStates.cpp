
#include "Base.h"
#include "EnemyStates.h"
#include "Game\Game.h"
#include "CA_Assert.h"


/**
 * 
 */
EnemyStateIdle::EnemyStateIdle()
{
}

/**
 * 
 */
EnemyStateIdle::~EnemyStateIdle()
{

}

/**
 * 
 */
void EnemyStateIdle::Enter(IController *pController_)
{

}

/**
 * 
 */
void EnemyStateIdle::Execute(IController *pController_, GameTime elpasedTime_)
{

}

/**
 * 
 */
void EnemyStateIdle::Exit(IController *pController_)
{

}

/**
 * 
 */
bool EnemyStateIdle::OnMessage(IController *pController_, const Telegram& )
{
	return false;
}
