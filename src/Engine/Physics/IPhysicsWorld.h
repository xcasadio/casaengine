#ifndef IPHYSICSWORLD_H_
#define IPHYSICSWORLD_H_

#include "CA_Export.h"

#include "Maths\Vector3.h"
#include "Maths\Shape\IShape.h"

#include "Memory\MemoryAllocation.h"
#include "GameTime.h"
#include "RigidBody.h"
#include "PhysicsObjectContainer.h"

namespace CasaEngine
{
	class CA_EXPORT IPhysicsWorld :
		public AllocatedObject<IPhysicsWorld>
	{
	public:
		IPhysicsWorld();
		virtual ~IPhysicsWorld();

		virtual void Update(const GameTime& gameTime_) = 0;

		virtual void SetGravity(const Vector3F& gravity_) = 0;
		virtual Vector3F GetGravity() const = 0;

		virtual ICollisionObjectContainer* CreateCollisionShape(const IShape* pShape_, const Vector3F& origin_) = 0;

		virtual void AddCollisionObject(ICollisionObjectContainer*) = 0;
		virtual void RemoveCollisionObject(ICollisionObjectContainer*) = 0;

		virtual IRigidBodyContainer* AddRigidBody(const RigidBody* pRigidBody_, Vector3F position) = 0;
		virtual void RemoveRigidBody(IRigidBodyContainer*) = 0;
	};
}

#endif
