#ifndef STATE_H_
#define STATE_H_

#include "GameTime.h"

namespace CasaEngine
{
	struct Telegram;

	template <class entity_type>
	class IState : public AllocatedObject<IState<entity_type>>
	{
	public:
		virtual ~IState(){}

		virtual void Enter(entity_type*) = 0;
		virtual void Execute(entity_type*, const GameTime &elapsedTime_) = 0;
		virtual void Exit(entity_type*) = 0;
		virtual bool OnMessage(entity_type*, const Telegram&) = 0;
	};

}

#endif
