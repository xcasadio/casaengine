//------------------------------------------------------------------------
//
//  Name:   MinersWifeOwnedStates.h
//
//  Desc:   All the states that can be assigned to the MinersWife class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#ifndef MINERSWIFE_OWNED_STATES_H
#define MINERSWIFE_OWNED_STATES_H

#include "AI\FSM\IState.h"
#include "AI\Messaging\Telegram.h"

using namespace CasaEngine;

class MinersWifeComponent;

//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class WifesGlobalState : public IState<MinersWifeComponent>
{
private:

	WifesGlobalState() {}

	//copy ctor and assignment should be private
	WifesGlobalState(const WifesGlobalState&);
	WifesGlobalState& operator=(const WifesGlobalState&);

public:

	//this is a singleton
	static WifesGlobalState* Instance();

	virtual void Enter(MinersWifeComponent* wife) {}

	virtual void Execute(MinersWifeComponent* wife, const GameTime& elapsedTime_);

	virtual void Exit(MinersWifeComponent* wife) {}

	virtual bool OnMessage(MinersWifeComponent* wife, const Telegram& msg);
};

//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DoHouseWork : public IState<MinersWifeComponent>
{
private:

	DoHouseWork() {}

	//copy ctor and assignment should be private
	DoHouseWork(const DoHouseWork&);
	DoHouseWork& operator=(const DoHouseWork&);

public:

	//this is a singleton
	static DoHouseWork* Instance();

	virtual void Enter(MinersWifeComponent* wife);

	virtual void Execute(MinersWifeComponent* wife, const GameTime& elapsedTime_);

	virtual void Exit(MinersWifeComponent* wife);

	virtual bool OnMessage(MinersWifeComponent* wife, const Telegram& msg);
};

//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class VisitBathroom : public IState<MinersWifeComponent>
{
private:

	VisitBathroom() {}

	//copy ctor and assignment should be private
	VisitBathroom(const VisitBathroom&);
	VisitBathroom& operator=(const VisitBathroom&);

public:

	//this is a singleton
	static VisitBathroom* Instance();

	virtual void Enter(MinersWifeComponent* wife);

	virtual void Execute(MinersWifeComponent* wife, const GameTime& elapsedTime_);

	virtual void Exit(MinersWifeComponent* wife);

	virtual bool OnMessage(MinersWifeComponent* wife, const Telegram& msg);
};

//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class CookStew : public IState<MinersWifeComponent>
{
private:

	CookStew() {}

	//copy ctor and assignment should be private
	CookStew(const CookStew&);
	CookStew& operator=(const CookStew&);

public:

	//this is a singleton
	static CookStew* Instance();

	virtual void Enter(MinersWifeComponent* wife);

	virtual void Execute(MinersWifeComponent* wife, const GameTime& elapsedTime_);

	virtual void Exit(MinersWifeComponent* wife);

	virtual bool OnMessage(MinersWifeComponent* wife, const Telegram& msg);
};

#endif