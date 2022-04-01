#ifndef BULLETPHYSICSWORLD_H_
#define BULLETPHYSICSWORLD_H_

#include "CA_Export.h"

#include "BulletDynamics\Dynamics\btDynamicsWorld.h"
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

		~BulletPhysicsWorld();

		void Update(const GameTime& gameTime_) override;

		void SetGravity(const Vector3F& gravity_) override;
		Vector3F GetGravity() const override;

		void setDebugDraw(btIDebugDraw* pIDebugDraw_);

		IRigidBodyContainer* AddRigidBody(const RigidBody* pRigidBody_, const Vector3F position) override;
		void RemoveRigidBody(IRigidBodyContainer* pObj_) override;

		void AddCollisionObject(ICollisionObjectContainer* pObj_) override;
		void RemoveCollisionObject(ICollisionObjectContainer* pObj_) override;

		ICollisionObjectContainer* CreateCollisionShape(const IShape* pShape_, const Vector3F& origin_) override;

	private:
		void AddCollisionObject(btCollisionObject* pColObj_);
		//btCollisionShape *CreateCollisionShape(const MeshComponentColliper *pMeshCollider_);
		btCollisionShape* CreateCollisionShape(const IShape* pShape_);
		void RemoveCollisionObject(btCollisionObject* pShape_);

		btCollisionObject* CreateCollisionObjectFromShape(IShape* pShape_);
		btCollisionObject* CreateCollisionObjectFromShape(btCollisionShape* pshape_, Vector3F center_);

	private:
		//btDiscreteDynamicsWorld* m_pBulletWorld;
		btDynamicsWorldExt* m_pBulletWorld;
	};
}

#endif // BULLETPHYSICSWORLD_H_
