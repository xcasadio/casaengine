#include "MinersWifeOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersWifeComponent.h"
#include "Locations.h"
#include "MessageTypes.h"

#include "AI\Messaging\Telegram.h"
#include <iostream>
#include "Maths\Random.h"
#include "..\FSMGame.h"
#include "Log\LogVerbose.h"
#include "Log\LogManager.h"
#include "DateTime.h"
#include "AI\Messaging\MessageDispatcher.h"
#include "Graphics\Color.h"
#include "MinersWifeComponent.h"
#include "Tools\InGameLogger.h"
#include "Config.h"


using namespace CasaEngine;

//-----------------------------------------------------------------------Global state

WifesGlobalState* WifesGlobalState::Instance()
{
  static WifesGlobalState instance;

  return &instance;
}


void WifesGlobalState::Execute(MinersWifeComponent* wife, const GameTime &elapsedTime_)
{
  //1 in 10 chance of needing the bathroom (provided she is not already
  //in the bathroom)
  if ( (RandFloat() < 0.1f) && 
       !wife->GetFSM()->isInState(*VisitBathroom::Instance()) )
  {
    wife->GetFSM()->ChangeState(VisitBathroom::Instance());
  }
}

bool WifesGlobalState::OnMessage(MinersWifeComponent* wife, const Telegram& msg)
{
  //SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
  case Msg_HiHoneyImHome:
	  {
		  CA_DEBUG("Message handled by (%d)%s\n", 
			  wife->GetEntity()->ID(), wife->GetEntity()->GetName());
		  InGameLog(logDelay, "%s: %s", wife->GetEntity()->GetName(), "Hi honey. Let me make you some of mah fine country stew");
		  wife->GetFSM()->ChangeState(CookStew::Instance());
	  }

   return true;

  }//end switch

  return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoHouseWork* DoHouseWork::Instance()
{
  static DoHouseWork instance;

  return &instance;
}


void DoHouseWork::Enter(MinersWifeComponent* wife)
{
	InGameLog(logDelay, "%s: %s", wife->GetEntity()->GetName(), "Time to do some more housework!");
}


void DoHouseWork::Execute(MinersWifeComponent* wife, const GameTime &elapsedTime_)
{
  switch(RandInt(0,2))
  {
  case 0:
    InGameLog(logDelay, "%s: %s", wife->GetEntity()->GetName(), "Moppin' the floor");
    break;

  case 1:

    InGameLog(logDelay, "%s: %s", wife->GetEntity()->GetName(), "Washin' the dishes");

    break;

  case 2:

    InGameLog(logDelay, "%s: %s", wife->GetEntity()->GetName(), "Makin' the bed");

    break;
  }
}

void DoHouseWork::Exit(MinersWifeComponent* wife)
{
}

bool DoHouseWork::OnMessage(MinersWifeComponent* wife, const Telegram& msg)
{
  return false;
}

//------------------------------------------------------------------------VisitBathroom

VisitBathroom* VisitBathroom::Instance()
{
  static VisitBathroom instance;

  return &instance;
}


void VisitBathroom::Enter(MinersWifeComponent* wife)
{  
  InGameLog(logDelay, "%s: %s", wife->GetEntity()->GetName(), "Walkin' to the can. Need to powda mah pretty li'lle nose"); 
}


void VisitBathroom::Execute(MinersWifeComponent* wife, const GameTime &elapsedTime_)
{
  InGameLog(logDelay, "%s: %s", wife->GetEntity()->GetName(), "Ahhhhhh! Sweet relief!");

  wife->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(MinersWifeComponent* wife)
{
  InGameLog(logDelay, "%s: %s", wife->GetEntity()->GetName(), "Leavin' the Jon");
}


bool VisitBathroom::OnMessage(MinersWifeComponent* wife, const Telegram& msg)
{
  return false;
}


//------------------------------------------------------------------------CookStew

CookStew* CookStew::Instance()
{
  static CookStew instance;

  return &instance;
}


void CookStew::Enter(MinersWifeComponent* wife)
{
  //if not already cooking put the stew in the oven
  if (!wife->Cooking())
  {
    InGameLog(logDelay, "%s: %s", wife->GetEntity()->GetName(), "Putting the stew in the oven");
  
    //send a delayed message myself so that I know when to take the stew
    //out of the oven
    MsgDispatcher.DispatchMsg(1.5f,                  //time delay
                              wife->GetEntity()->ID(),           //sender ID
                              wife->GetEntity()->ID(),           //receiver ID
                              Msg_StewReady,        //msg
                              NO_ADDITIONAL_INFO); 

    wife->SetCooking(true);
  }
}


void CookStew::Execute(MinersWifeComponent* wife, const GameTime &elapsedTime_)
{
  InGameLog(logDelay, "%s: %s", wife->GetEntity()->GetName(), "Fussin' over food");
}

void CookStew::Exit(MinersWifeComponent* wife)
{
  InGameLog(logDelay, "%s: %s", wife->GetEntity()->GetName(), "Puttin' the stew on the table");
}


bool CookStew::OnMessage(MinersWifeComponent* wife, const Telegram& msg)
{
  //SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
    case Msg_StewReady:
    {
      CA_DEBUG("Message received by (%d)%s at time: %s", 
		  wife->GetEntity()->ID(), wife->GetEntity()->GetName(), DateTime::Now().GetCurrentTime().c_str());
      InGameLog(logDelay, "%s: %s", wife->GetEntity()->GetName(), "StewReady! Lets eat");

      //let hubby know the stew is ready
      MsgDispatcher.DispatchMsg(SEND_MSG_IMMEDIATELY,
                                wife->GetEntity()->ID(),
                                wife->GetMinerID(),
                                Msg_StewReady,
                                NO_ADDITIONAL_INFO);

      wife->SetCooking(false);

      wife->GetFSM()->ChangeState(DoHouseWork::Instance());     
    }

    return true;

  }//end switch

  return false;
}