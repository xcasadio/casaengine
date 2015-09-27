#ifndef BOX2DCOLLIDERCOMPONENT_H_
#define BOX2DCOLLIDERCOMPONENT_H_

#include <string>
#include <iosfwd>

#include "CA_Export.h"
#include "GameTime.h"
#include "ColliderComponent.h"
#include "Maths/Shape/Box2D.h"


namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT Box2DColliderComponent :
		public ColliderComponent
	{
	private:

	public:
		Box2DColliderComponent(BaseEntity* pEntity_);
		~Box2DColliderComponent();

		//all entities must implement an Initialize function
		//void Initialize();

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

#endif // BOX2DCOLLIDERCOMPONENT_H_
