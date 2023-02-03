#pragma once

#include "CA_Export.h"

#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "BulletCollision/CollisionDispatch/btCollisionDispatcher.h"
#include "BulletCollision/BroadphaseCollision/btDispatcher.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"

#include "Maths/Shape/IShape.h"
#include "Maths/Vector3.h"
#include "Physics/IPhysicsWorld.h"

#include "Physics/PhysicsObjectContainer.h"
#include "../Collision.h"
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

namespace CasaEngine
{
	class CA_EXPORT BulletPhysicsWorld :
		public IPhysicsWorld
	{
	public:
		BulletPhysicsWorld(
			btDefaultCollisionConfiguration* pConfig_,
			btCollisionDispatcher* pDispatcher_,
			btBroadphaseInterface* pOverlappingPairCache_,
			btSequentialImpulseConstraintSolver* pConstraintSolver_);

		~BulletPhysicsWorld() override;

		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		void SetGravity(const Vector3& gravity_) override;
		Vector3 GetGravity() const override;

		void setDebugDraw(btIDebugDraw* IDebugDraw);

		IRigidBodyContainer* AddRigidBody(BaseEntity* entity, const RigidBodyParameters* pRigidBody_, const Vector3& position) override;
		void RemoveRigidBody(IRigidBodyContainer* pObj_) override;

		void AddCollisionObject(ICollisionObjectContainer* pObj_) override;
		void RemoveCollisionObject(ICollisionObjectContainer* pObj_) override;

		ICollisionObjectContainer* CreateCollisionShape(BaseEntity* entity, IShape* shape, const Vector3& origin, CollisionHitType hitType = CollisionHitType::Unknown, CollisionFlags flags = CollisionFlags::Dynamic) override;
		ICollisionObjectContainer* CreateSensor(BaseEntity* entity, IShape* shape, const Vector3& origin, CollisionHitType hitType) override;

		void ContactTest(ICollisionObjectContainer* collision_object_container) override;

	private:
		void AddCollisionObject(btCollisionObject* pColObj_);
		btCollisionShape* CreateCollisionShape(const IShape* pShape_);
		void RemoveCollisionObject(btCollisionObject* collisionObject);

		btCollisionObject* CreateCollisionObjectFromShape(IShape* shape);
		btCollisionObject* CreateCollisionObjectFromShape(btCollisionShape* shape, Vector3 center);

	private:
		btDiscreteDynamicsWorld* _bulletWorld;
		btCollisionDispatcher* _dispatcher;
	};
}
