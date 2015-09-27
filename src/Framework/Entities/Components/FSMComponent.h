#ifndef FSMCOMPONENT_H_
#define FSMCOMPONENT_H_

#include <string>

#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>
#include "Entities/Component.h"
#include <string>
#include "AI/FSM/StateMachine.h"

namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT FSMComponent :
		public Component
	{
	private:
		StateMachine<BaseEntity>*  m_pStateMachine;
		
	public:
		FSMComponent(BaseEntity* pEntity_);
		virtual ~FSMComponent();

		StateMachine<BaseEntity>* GetFSM() const;

		//
		void Initialize();

		//all entities must implement an update function
		void  Update(const GameTime& gameTime_);

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);

		//entities should be able to read/write their data to a stream
		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);
	};

}

#endif // FSMCOMPONENT_H_


