#ifndef PHYSICSENGINE_H_
#define PHYSICSENGINE_H_

#include "CA_Export.h"

#include "IPhysicsWorld.h"
#include "IPhysicsEngine.h"
#include "BulletCollision\CollisionDispatch\btCollisionDispatcher.h"
#include "BulletCollision\BroadphaseCollision\btDispatcher.h"
#include "BulletCollision\CollisionDispatch\btDefaultCollisionConfiguration.h"
#include "BulletCollision\BroadphaseCollision\btBroadphaseInterface.h"
#include "BulletDynamics\ConstraintSolver\btSequentialImpulseConstraintSolver.h"

namespace CasaEngine
{
	class CA_EXPORT PhysicsEngine
	{
	public:
		PhysicsEngine();
		~PhysicsEngine();

		void Initialize();
		IPhysicsWorld* CreateWorld() const;
		IPhysicsEngine* GetPhysicsEngineImpl() const;

	private:
		IPhysicsEngine* m_pPhysicsEngine;
	};
}

#endif
