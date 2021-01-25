#ifndef BULLETPHYSICSENGINE_H_
#define BULLETPHYSICSENGINE_H_

#include "CA_Export.h"

#include "Physics/IPhysicsWorld.h"
#include "Physics\IPhysicsEngine.h"

#include "BulletCollision\CollisionDispatch\btCollisionDispatcher.h"
#include "BulletCollision\BroadphaseCollision\btDispatcher.h"
#include "BulletCollision\CollisionDispatch\btDefaultCollisionConfiguration.h"
#include "BulletCollision\BroadphaseCollision\btBroadphaseInterface.h"
#include "BulletDynamics\ConstraintSolver\btSequentialImpulseConstraintSolver.h"
#include "LinearMath\btIDebugDraw.h"

namespace CasaEngine
{
	/**
	 *
	 */
	class CA_EXPORT BulletPhysicsEngine :
		public IPhysicsEngine
	{
	private:
		btDefaultCollisionConfiguration* m_pCollisionConfig;
		btCollisionDispatcher* m_pDispatcher;
		btBroadphaseInterface* m_pOverlappingPairCache;
		btSequentialImpulseConstraintSolver* m_pConstraintSolver;
		btIDebugDraw* m_pIDebugDraw;

	public:
		/**
		 *
		 */
		BulletPhysicsEngine();

		/**
		 *
		 */
		~BulletPhysicsEngine();

		/**
		 *
		 */
		void Initialize() override;

		/**
		 *
		 */
		void SetPhysicsDebugDraw(btIDebugDraw* pDebugDraw_);

		/**
		 *
		 */
		IPhysicsWorld* CreateWorld() const override;
	};
}

#endif // BULLETPHYSICSENGINE_H_
