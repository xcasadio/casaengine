#include "MinerOwnedStates.h"
#include "MinerComponent.h"
#include "Locations.h"
#include "MessageTypes.h"


#include <iostream>
#include "AI\Messaging\Telegram.h"
#include "..\FSMGame.h"
#include "AI\Messaging\MessageDispatcher.h"
#include "Log\LogManager.h"
#include "DateTime.h"
#include <stdlib.h>
#include <iosfwd>
#include "MinerComponent.h"
#include "Tools\InGameLogger.h"
#include "Config.h"

using namespace CasaEngine;

//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
  static EnterMineAndDigForNugget instance;
  return &instance;
}


void EnterMineAndDigForNugget::Enter(MinerComponent* pMiner)
{
  //if the miner is not already located at the goldmine, he must
  //change location to the gold mine
  if (pMiner->Location() != goldmine)
  {
    InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "Walkin' to the goldmine");
    pMiner->ChangeLocation(goldmine);
  }
}


void EnterMineAndDigForNugget::Execute(MinerComponent* pMiner, const GameTime &elapsedTime_)
{  
  //Now the miner is at the goldmine he digs for gold until he
  //is carrying in excess of MaxNuggets. If he gets thirsty during
  //his digging he packs up work for a while and changes state to
  //gp to the saloon for a whiskey.
  pMiner->AddToGoldCarried(1);

  pMiner->IncreaseFatigue();

  InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "Pickin' up a nugget");

  //if enough gold mined, go and put it in the bank
  if (pMiner->PocketsFull())
  {
    pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
  }

  if (pMiner->Thirsty())
  {
    pMiner->GetFSM()->ChangeState(QuenchThirst::Instance());
  }
}


void EnterMineAndDigForNugget::Exit(MinerComponent* pMiner)
{
  InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "Ah'm leavin' the goldmine with mah pockets full o' sweet gold");
}


bool EnterMineAndDigForNugget::OnMessage(MinerComponent* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
  static VisitBankAndDepositGold instance;

  return &instance;
}

void VisitBankAndDepositGold::Enter(MinerComponent* pMiner)
{  
  //on entry the miner makes sure he is located at the bank
  if (pMiner->Location() != bank)
  {
    InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "Goin' to the bank. Yes sire");

    pMiner->ChangeLocation(bank);
  }
}


void VisitBankAndDepositGold::Execute(MinerComponent* pMiner, const GameTime &elapsedTime_)
{
  //deposit the gold
  pMiner->AddToWealth(pMiner->GoldCarried());
    
  pMiner->SetGoldCarried(0);

  std::ostringstream msg;
  msg << pMiner->GetEntity()->GetName() << ": Depositing gold. Total savings now: " << pMiner->Wealth();
  InGameLog(logDelay, msg.str().c_str());

  //wealthy enough to have a well earned rest?
  if (pMiner->Wealth() >= ComfortLevel)
  {
    InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "WooHoo! Rich enough for now. Back home to mah li'lle lady");      
    pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());      
  }
  //otherwise get more gold
  else 
  {
    pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
  }
}


void VisitBankAndDepositGold::Exit(MinerComponent* pMiner)
{
  InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "Leavin' the bank");
}


bool VisitBankAndDepositGold::OnMessage(MinerComponent* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
  static GoHomeAndSleepTilRested instance;

  return &instance;
}

void GoHomeAndSleepTilRested::Enter(MinerComponent* pMiner)
{
  if (pMiner->Location() != shack)
  {
    InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "Walkin' home");

    pMiner->ChangeLocation(shack); 

    //let the wife know I'm home
    MsgDispatcher.DispatchMsg(SEND_MSG_IMMEDIATELY, //time delay
                              pMiner->GetEntity()->ID(),        //ID of sender
                              pMiner->GetWifeID(),            //ID of recipient
                              Msg_HiHoneyImHome,   //the message
                              NO_ADDITIONAL_INFO);    
  }
}

void GoHomeAndSleepTilRested::Execute(MinerComponent* pMiner, const GameTime &elapsedTime_)
{ 
  //if miner is not fatigued start to dig for nuggets again.
  if (!pMiner->Fatigued())
  {
     InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "All my fatigue has drained away. Time to find more gold!");
     pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
  }
  else 
  {
    //sleep
    pMiner->DecreaseFatigue();
    InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "ZZZZ...");
  } 
}

void GoHomeAndSleepTilRested::Exit(MinerComponent* pMiner)
{ 
}


bool GoHomeAndSleepTilRested::OnMessage(MinerComponent* pMiner, const Telegram& msg)
{
   //SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

   switch(msg.Msg)
   {
   case Msg_StewReady:
     CA_DEBUG("Message handled by (%d)%s\n", 
		 pMiner->GetEntity()->ID(), pMiner->GetEntity()->GetName());

     //SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);

     InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "Okay Hun, ahm a comin'!");

     pMiner->GetFSM()->ChangeState(EatStew::Instance());
      
     return true;

   }//end switch

   return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
  static QuenchThirst instance;

  return &instance;
}

void QuenchThirst::Enter(MinerComponent* pMiner)
{
  if (pMiner->Location() != saloon)
  {    
    pMiner->ChangeLocation(saloon);
    InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "Boy, ah sure is thusty! Walking to the saloon");
  }
}

void QuenchThirst::Execute(MinerComponent* pMiner, const GameTime &elapsedTime_)
{
  pMiner->BuyAndDrinkAWhiskey();
  InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "That's mighty fine sippin' liquer");
  pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());  
}


void QuenchThirst::Exit(MinerComponent* pMiner)
{ 
  InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "Leaving the saloon, feelin' good");
}


bool QuenchThirst::OnMessage(MinerComponent* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance()
{
  static EatStew instance;

  return &instance;
}


void EatStew::Enter(MinerComponent* pMiner)
{
  InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "Smells Reaaal goood Elsa!");
}

void EatStew::Execute(MinerComponent* pMiner, const GameTime &elapsedTime_)
{
  InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "Tastes real good too!");

  pMiner->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(MinerComponent* pMiner)
{ 
  InGameLog(logDelay, "%s: %s", pMiner->GetEntity()->GetName(), "Thankya li'lle lady. Ah better get back to whatever ah wuz doin'");
}


bool EatStew::OnMessage(MinerComponent* pMiner, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}


