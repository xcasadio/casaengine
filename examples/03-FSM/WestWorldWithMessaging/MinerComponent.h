//------------------------------------------------------------------------
//
//  Name:   Miner.h
//
//  Desc:   A class defining a goldminer.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#ifndef MINERCOMPONENT_H_
#define MINERCOMPONENT_H_

#include <iosfwd>

#include "Entities/Component.h"
#include "Locations.h"
#include "AI/FSM/StateMachine.h"

using namespace CasaEngine;

//the amount of gold a miner must have before he feels he can go home
const int ComfortLevel = 5;
//the amount of nuggets a miner can carry
const int MaxNuggets = 3;
//above this value a miner is thirsty
const int ThirstLevel = 5;
//above this value a miner is sleepy
const int TirednessThreshold = 5;

/**
 *
 */
class MinerComponent :
	public Component
{
private:
	StateMachine<MinerComponent>* m_pStateMachine;

	location_type         m_Location;

	//how many nuggets the miner has in his pockets
	int                   m_iGoldCarried;

	int                   m_iMoneyInBank;

	//the higher the value, the thirstier the miner
	int                   m_iThirst;

	//the higher the value, the more tired the miner
	int                   m_iFatigue;

	//used to create some latency between each update
	float m_Delay;

	int m_WifeID;

public:
	MinerComponent(BaseEntity* pEntity_);
	~MinerComponent();

	StateMachine<MinerComponent>* GetFSM() const;

	//
	virtual void Initialize();

	//all entities must implement an update function
	virtual void  Update(const GameTime& gameTime_);

	virtual bool HandleMessage(const Telegram& msg);

	//all entities can communicate using messages. They are sent
	//using the MessageDispatcher singleton class
	//void HandleEvent(const Event* pEvent_);

	//entities should be able to read/write their data to a stream
	void Write(std::ostream& os)const;
	void Read(std::ifstream& is);

	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	int           GoldCarried()const { return m_iGoldCarried; }
	void          SetGoldCarried(int val) { m_iGoldCarried = val; }
	void          AddToGoldCarried(int val);
	bool          PocketsFull()const { return m_iGoldCarried >= MaxNuggets; }

	bool          Fatigued()const;
	void          DecreaseFatigue() { m_iFatigue -= 1; }
	void          IncreaseFatigue() { m_iFatigue += 1; }

	int           Wealth()const { return m_iMoneyInBank; }
	void          SetWealth(int val) { m_iMoneyInBank = val; }
	void          AddToWealth(int val);

	bool          Thirsty()const;
	void          BuyAndDrinkAWhiskey() { m_iThirst = 0; m_iMoneyInBank -= 2; }

	int GetWifeID() const { return m_WifeID; }
	void SetWifeID(int val) { m_WifeID = val; }
};

#endif // MINERCOMPONENT_H_
