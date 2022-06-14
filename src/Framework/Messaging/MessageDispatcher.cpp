#include "Base.h"
#include "MessageDispatcher.h"
#include "Entities/BaseEntity.h"
#include "Entities/EntityManager.h"
#include "Log/LogVerbose.h"
#include "Log/LogManager.h"
#include "GameTime.h"

#include "Game/Game.h"

namespace CasaEngine
{
	//uncomment below to send message info to the debug window
	//#define SHOW_MESSAGING_INFO

	//----------------------------- Dispatch ---------------------------------
	//  
	//  see description in header
	//------------------------------------------------------------------------
		void MessageDispatcher::Discharge(BaseEntity* pReceiver, const Telegram& telegram)
	{
		if (!pReceiver->HandleMessage(telegram))
		{
			//telegram could not be handled
			CA_DEBUG("MessageDispatcher::Discharge() : Message not handled, receiver Id (%d)%s\n",
				pReceiver->Id(), pReceiver->GetName());
		}
	}

	//---------------------------- DispatchMsg ---------------------------
	//
	//  given a message, a receiver, a sender and any time delay, this function
	//  routes the message to the correct agent (if no delay) or stores
	//  in the message queue to be dispatched at the correct time
	//------------------------------------------------------------------------
	void MessageDispatcher::DispatchMsg(float        delay,
		int          sender,
		int          receiver,
		int          msg,
		void* AdditionalInfo)
	{

		//get a pointer to the receiver
		BaseEntity* pReceiver = Game::Instance().GetEntityManager().GetEntityFromId(receiver);

		//for debugging
		BaseEntity* pSender = Game::Instance().GetEntityManager().GetEntityFromId(sender);
		const char* senderName = (pSender == nullptr ? "" : pSender->GetName());

		//make sure the receiver is valid
		if (pReceiver == nullptr)
		{
			CA_WARN("MessageDispatcher::DispatchMsg() : No Receiver with Id of %d found\n", receiver);
			return;
		}

		//create the telegram
		Telegram telegram(0, sender, receiver, msg, AdditionalInfo);

		//if there is no delay, route telegram immediately                       
		if (delay <= 0.0f)
		{
			CA_DEBUG("Telegram dispatched by (%d)%s for (%d)%s. Msg is %d\n",
				sender, senderName, receiver, pReceiver->GetName(), msg);

			//send the telegram to the recipient
			Discharge(pReceiver, telegram);
		}
		//else calculate the time when the telegram should be dispatched
		else
		{
			telegram.DispatchTime = delay;

			//and put it in the queue
			PriorityQ.insert(telegram);

			CA_DEBUG("Delayed telegram from (%d)%s recorded for (%d)%s. Msg is %d\n",
				sender, senderName, receiver, pReceiver->GetName(), msg);
		}
	}

	//---------------------- DispatchDelayedMessages -------------------------
	//
	//  This function dispatches any telegrams with a timestamp that has
	//  expired. Any dispatched telegrams are removed from the queue
	//------------------------------------------------------------------------
	void MessageDispatcher::DispatchDelayedMessages(const GameTime& gameTime_)
	{
		//first get current time
		float CurrentTime = gameTime_.FrameTime();

		//now peek at the queue to see if any telegrams need dispatching.
		//remove all telegrams from the front of the queue that have gone
		//past their sell by date
		while (!PriorityQ.empty() &&
			(PriorityQ.begin()->DispatchTime < CurrentTime) &&
			(PriorityQ.begin()->DispatchTime > 0))
		{
			//read the telegram from the front of the queue
			const Telegram& telegram = *PriorityQ.begin();

			//find the recipient
			BaseEntity* pReceiver = Game::Instance().GetEntityManager().GetEntityFromId(telegram.Receiver);

			if (pReceiver != nullptr)
			{
				CA_DEBUG("Queued telegram ready for dispatch: sent to (%d)%s. Msg is %d\n",
					pReceiver->Id(), pReceiver->GetName(), telegram.Msg);

				//send the telegram to the recipient
				Discharge(pReceiver, telegram);
			}
			else
			{
				CA_ERROR("Queued telegram ready for dispatch: can't find the entity '%d'. Msg is %d\n",
					telegram.Receiver, telegram.Msg);
			}

			//remove it from the queue
			PriorityQ.erase(PriorityQ.begin());
		}
	}

}
