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
    //set animation stand
    pController_->GetCharacter()->SetCurrentAnimation(0); // direction
}

/**
 * 
 */
void EnemyStateIdle::Execute(IController *pController_, const GameTime& elpasedTime_)
{
    //delay action
	
    if (false)//can attack)
    {
        //e->mov = ATTACK;
    }
    else if (rand() % 10 == 7)
    {
        //e->mov = IMMOBILE;
        //e->dir = rand() % 4 + 1;
    }
    else 
    {
        pController_->FSM()->ChangeState(pController_->GetState(static_cast<int>(EnemyControllerState::MOVING)));
    }
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



/**
 *
 */
EnemyStateWalking::EnemyStateWalking()
{
}

/**
 *
 */
EnemyStateWalking::~EnemyStateWalking()
{
    
}

/**
 *
 */
void EnemyStateWalking::Enter(IController* pController_)
{
    //set animation stand
    pController_->GetCharacter()->SetCurrentAnimation(1); // direction
}

/**
 *
 */
void EnemyStateWalking::Execute(IController* pController_, const GameTime& elpasedTime_)
{
    //arrive to the target
	
}

/**
 *
 */
void EnemyStateWalking::Exit(IController* pController_)
{

}

/**
 *
 */
bool EnemyStateWalking::OnMessage(IController* pController_, const Telegram&)
{
	//end animation?
    return false;
}
