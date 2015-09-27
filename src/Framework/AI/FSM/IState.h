
#ifndef STATE_H_
#define STATE_H_
//------------------------------------------------------------------------
//
//  Name:   IState.h
//
//  Desc:   abstract base class to define an interface for a state
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include "GameTime.h"

namespace CasaEngine
{
	struct Telegram;

	/*
	 *	
	 */
	template <class entity_type>
	class IState
	{
	public:

		virtual ~IState(){}

		//this will execute when the state is entered
		virtual void Enter(entity_type*) = 0;

		//this is the states normal update function
		virtual void Execute(entity_type*, const GameTime &elapsedTime_) = 0;

		//this will execute when the state is exited. 
		virtual void Exit(entity_type*) = 0;

		//this executes if the agent receives a message from the 
		//message dispatcher
		virtual bool OnMessage(entity_type*, const Telegram&) = 0;
	};

} // namespace CasaEngine

#endif // STATE_H_