#pragma once

#include  "GameTime.hpp"

namespace CasaEngine
{
	struct Telegram;

	template <class entity_type>
	class IState
	{
	public:
		IState() = default;
		virtual ~IState() = default;

		virtual void Enter(entity_type*) = 0;
		virtual void Execute(entity_type*, const GameTime &elapsedTime_) = 0;
		virtual void Exit(entity_type*) = 0;
		virtual bool OnMessage(entity_type*, const Telegram&) = 0;
	};
}
