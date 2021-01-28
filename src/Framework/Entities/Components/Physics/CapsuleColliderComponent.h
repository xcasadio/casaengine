#ifndef CAPSULECOLLIDERCOMPONENT_H_
#define CAPSULECOLLIDERCOMPONENT_H_

#include <iosfwd>

#include "CA_Export.h"
#include "ColliderComponent.h"

namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT CapsuleColliderComponent :
		public ColliderComponent
	{
	private:
		//PhysicMaterial* m_pPhysicMaterial;
		bool m_IsTrigger;


	public:
		CapsuleColliderComponent(BaseEntity* pEntity_);
		virtual ~CapsuleColliderComponent();

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

#endif // CAPSULECOLLIDERCOMPONENT_H_


