#pragma once

#include "CA_Export.h"

#include "BulletDynamics\ConstraintSolver\btSequentialImpulseConstraintSolver.h"
#include "BulletCollision\CollisionDispatch\btCollisionDispatcher.h"
#include "BulletCollision\BroadphaseCollision\btDispatcher.h"
#include "BulletCollision\CollisionDispatch\btDefaultCollisionConfiguration.h"

#include "Maths\Shape\IShape.h"
#include "Maths\Vector3.h"
#include "Physics\IPhysicsWorld.h"
#include "btDynamicsWorldExt.h"

#include "Physics\PhysicsObjectContainer.h"

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

		ICollisionObjectContainer* CreateCollisionShape(const IShape* shape_, const Vector3& origin_) override;

	private:
		void AddCollisionObject(btCollisionObject* pColObj_);
		//btCollisionShape *CreateCollisionShape(const MeshComponentColliper *pMeshCollider_);
		btCollisionShape* CreateCollisionShape(const IShape* pShape_);
		void RemoveCollisionObject(btCollisionObject* collisionObject);

		btCollisionObject* CreateCollisionObjectFromShape(IShape* shape);
		btCollisionObject* CreateCollisionObjectFromShape(btCollisionShape* shape, Vector3 center);

	private:
		//btDiscreteDynamicsWorld* _bulletWorld;
		btDynamicsWorldExt* _bulletWorld;
		btCollisionDispatcher* _dispatcher;
	};
}
