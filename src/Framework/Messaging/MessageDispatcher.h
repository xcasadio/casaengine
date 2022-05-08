#pragma once

#include "Messaging/Telegram.h"
#include "CA_Export.h"
#include "GameTime.h"

#include <set>

namespace CasaEngine
{
	//#define MsgDispatcher Game::Instance().GetMessageDispatcher()
	class BaseEntity;

	//to make code easier to read
	const float SEND_MSG_IMMEDIATELY = 0.0f;
	const int    NO_ADDITIONAL_INFO = 0;
	const int    SENDER_ID_IRRELEVANT = -1;


	class CA_EXPORT MessageDispatcher
	{
	public:
		//send a message to another agent. Receiving agent is referenced by ID.
		void DispatchMsg(float      delay,
			int         sender,
			int         receiver,
			int         msg,
			void* AdditionalInfo = nullptr);

		//send out any delayed messages. This method is called each time through   
		//the main game loop.
		void DispatchDelayedMessages(const GameTime& gameTime_);
		
	private:
		//a std::set is used as the container for the delayed messages
		//because of the benefit of automatic sorting and avoidance
		//of duplicates. Messages are sorted by their dispatch time.
		std::set<Telegram> PriorityQ;

		//this method is utilized by DispatchMsg or DispatchDelayedMessages.
		//This method calls the message handling member function of the receiving
		//entity, pReceiver, with the newly created telegram
		void Discharge(BaseEntity* pReceiver, const Telegram& msg);
	};

}
