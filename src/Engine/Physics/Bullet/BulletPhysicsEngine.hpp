#pragma once

#include "CA_Export.hpp"

#include  "Physics/IPhysicsWorld.hpp"
#include  "Physics/IPhysicsEngine.hpp"

#include  "BulletCollision/CollisionDispatch/btCollisionDispatcher.h"
#include  "BulletCollision/BroadphaseCollision/btDispatcher.h"
#include  "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include  "BulletCollision/BroadphaseCollision/btBroadphaseInterface.h"
#include  "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"

namespace CasaEngine
{
	class CA_EXPORT BulletPhysicsEngine :
		public IPhysicsEngine
	{
	private:
		btDefaultCollisionConfiguration* m_pCollisionConfig;
		btCollisionDispatcher* m_pDispatcher;
		btBroadphaseInterface* m_pOverlappingPairCache;
		btSequentialImpulseConstraintSolver* m_pConstraintSolver;

	public:
		BulletPhysicsEngine();
		~BulletPhysicsEngine() override;

		void Initialize() override;

		IPhysicsWorld* CreateWorld() override;
	};
}
