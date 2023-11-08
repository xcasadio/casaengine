#pragma once

#include  "AI/FSM/StateMachine.hpp"
#include  "Entities/Component.hpp"
#include  "GameTime.hpp"
#include  "Locations.hpp"
#include <iosfwd>

using namespace CasaEngine;

/**
 *
 */
class MinersWifeComponent :
	public Component
{
private:
	StateMachine<MinersWifeComponent>* m_pStateMachine;

	location_type   m_Location;

	//is she presently cooking?
	bool            m_bCooking;

	//used to create some latence between each update
	float m_Delay;

	int m_MinerID;

public:
	MinersWifeComponent(BaseEntity* pEntity_);
	virtual ~MinersWifeComponent();

	StateMachine<MinersWifeComponent>* GetFSM() const;

	//
	virtual void Initialize();

	//all entities must implement an update function
	virtual void  Update(const GameTime& gameTime_);

	/**
	 *
	 */
	virtual bool HandleMessage(const Telegram& msg);

	//all entities can communicate using messages. They are sent
	//using the MessageDispatcher singleton class
	//void HandleEvent(const Event* pEvent_);

	//entities should be able to read/write their data to a stream
	void Write(std::ostream& os)const;
	void Read(std::ifstream& is);

	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool          Cooking()const { return m_bCooking; }
	void          SetCooking(bool val) { m_bCooking = val; }

	int GetMinerID() const { return m_MinerID; }
	void SetMinerID(int val) { m_MinerID = val; }
};
