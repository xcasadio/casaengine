#ifndef IPHYSICSWORLD_H_
#define IPHYSICSWORLD_H_

#include "CA_Export.h"

#include "Maths\Vector3.h"
#include "Maths\Shape\IShape.h"
#include "GameTime.h"
#include "RigidBody.h"
#include "PhysicsObjectContainer.h"

namespace CasaEngine
{
	class CA_EXPORT IPhysicsWorld
	{
	public:
		IPhysicsWorld();
		virtual ~IPhysicsWorld();

		virtual void Update(const GameTime& gameTime_) = 0;

		virtual void SetGravity(const Vector3& gravity_) = 0;
		virtual Vector3 GetGravity() const = 0;

		virtual ICollisionObjectContainer* CreateCollisionShape(const IShape* pShape_, const Vector3& origin_) = 0;

		virtual void AddCollisionObject(ICollisionObjectContainer*) = 0;
		virtual void RemoveCollisionObject(ICollisionObjectContainer*) = 0;

		virtual IRigidBodyContainer* AddRigidBody(const RigidBody* pRigidBody_, Vector3 position) = 0;
		virtual void RemoveRigidBody(IRigidBodyContainer*) = 0;
	};
}

#endif
