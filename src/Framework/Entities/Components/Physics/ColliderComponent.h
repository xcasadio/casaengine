#ifndef COLLIDERCOMPONENT_H_
#define COLLIDERCOMPONENT_H_

#include <iosfwd>

#include "CA_Export.h"

#include "GameTime.h"
#include "Entities/Component.h"
#include "Sprite/SpriteRenderer.h"
#include "Physics/PhysicsObjectContainer.h"

namespace CasaEngine
{

	/*
	 *	
	 */
	class CA_EXPORT ColliderComponent :
		public Component
	{
	private:
		//PhysicMaterial* m_pPhysicMaterial;
		bool m_IsTrigger;
		float m_Mass;

	protected:
		IShape *m_pShape;

	public:
		virtual ~ColliderComponent();

		//all entities must implement an Initialize function
		void Initialize();

		/**
		 * 
		 */
		void Update(const GameTime& gameTime_);

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);

		IShape *GetShape() const;

		float Mass() const;
		void Mass(float val);

		//entities should be able to read/write their data to a stream
		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);

	protected:
		ColliderComponent(BaseEntity* pEntity_, int type_);

	private:
		ICollisionObjectContainer *m_pCollisionObjectContainer;
	};

}

#endif // COLLIDERCOMPONENT_H_


