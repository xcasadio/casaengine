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
	/**
	 * The world that contains physics entities.
	 * It is a adapter to the bullet dynamics world
	 */
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

		void setDebugDraw(btIDebugDraw* pIDebugDraw_);

		IRigidBodyContainer* AddRigidBody(BaseEntity* entity, const RigidBody* pRigidBody_, Vector3 position) override;
		void RemoveRigidBody(IRigidBodyContainer* pObj_) override;

		void AddCollisionObject(ICollisionObjectContainer* pObj_) override;
		void RemoveCollisionObject(ICollisionObjectContainer* pObj_) override;

		ICollisionObjectContainer* CreateCollisionShape(const IShape* pShape_, const Vector3& origin_) override;

	private:
		void AddCollisionObject(btCollisionObject* pColObj_);
		//btCollisionShape *CreateCollisionShape(const MeshComponentColliper *pMeshCollider_);
		btCollisionShape* CreateCollisionShape(const IShape* pShape_);
		void RemoveCollisionObject(btCollisionObject* pShape_);

		btCollisionObject* CreateCollisionObjectFromShape(IShape* pShape_);
		btCollisionObject* CreateCollisionObjectFromShape(btCollisionShape* pshape_, Vector3 center_);

	private:
		//btDiscreteDynamicsWorld* m_pBulletWorld;
		btDynamicsWorldExt* m_pBulletWorld;
		btCollisionDispatcher* dispatcher_;
	};
}
