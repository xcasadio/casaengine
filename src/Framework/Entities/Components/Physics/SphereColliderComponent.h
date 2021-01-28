#ifndef SPHERECOLLIDERCOMPONENT_H_
#define SPHERECOLLIDERCOMPONENT_H_

#include <iosfwd>

#include "CA_Export.h"
#include "ColliderComponent.h"

namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT SphereColliderComponent :
		public ColliderComponent
	{
	private:

	public:
		SphereColliderComponent(BaseEntity* pEntity_);
		virtual ~SphereColliderComponent();

		//all entities must implement an Initialize function
		void Initialize();

		/**
		 * 
		 */
		void Draw();

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);

		//entities should be able to read/write their data to a stream
		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);
	};

}

#endif // SPHERECOLLIDERCOMPONENT_H_


