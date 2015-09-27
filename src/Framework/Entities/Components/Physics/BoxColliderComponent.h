#ifndef BOXCOLLIDERCOMPONENT_H_
#define BOXCOLLIDERCOMPONENT_H_

#include <string>
#include <iosfwd>

#include "CA_Export.h"
#include "GameTime.h"
#include "ColliderComponent.h"
#include "Maths/Shape/Box.h"


namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT BoxColliderComponent :
		public ColliderComponent
	{
	private:
		Box m_Shape;

	public:
		BoxColliderComponent(BaseEntity* pEntity_);
		~BoxColliderComponent();

		//all entities must implement an Initialize function
		void Initialize();

		/**
		 * 
		 */
		void Draw();


		Box Shape() const;

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);

		//entities should be able to read/write their data to a stream
		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);
	};

}

#endif // BOXCOLLIDERCOMPONENT_H_


