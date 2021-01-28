#ifdef USE_BULLET_PHYSICS

#include "btDynamicsWorldExt.h"
#include "CA_Assert.h"
#include "BulletCollision\CollisionShapes\btCollisionShape.h"
#include "LinearMath\btTransform.h"
#include "LinearMath\btVector3.h"
#include "BulletCollision\CollisionShapes\btBox2dShape.h"
#include "BulletCollision\CollisionDispatch\btCollisionWorld.h"
#include "LinearMath\btIDebugDraw.h"

namespace CasaEngine
{
	/**
	 *
	 */
	btDynamicsWorldExt::btDynamicsWorldExt(btDispatcher* dispatcher, btBroadphaseInterface* broadphase, btConstraintSolver* constraintSolver, btCollisionConfiguration* collisionConfiguration) :
		btDiscreteDynamicsWorld(dispatcher, broadphase, constraintSolver, collisionConfiguration)
	{
	}

	/**
	 *
	 */
	void btDynamicsWorldExt::debugDrawObject(const btTransform& worldTransform, const btCollisionShape* shape, const btVector3& color)
	{
		switch (shape->getShapeType())
		{
		case BOX_2D_SHAPE_PROXYTYPE:
		{
			const btBox2dShape* boxShape = static_cast<const btBox2dShape*>(shape);
			btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
			getDebugDrawer()->drawBox(-halfExtents, halfExtents, worldTransform, color);
			break;
		}

		/*case CONVEX_2D_SHAPE_PROXYTYPE:

			break;*/

		default:
		{
			btDynamicsWorld::debugDrawObject(worldTransform, shape, color);
			break;
		}
		}
	}
}

#endif // USE_BULLET_PHYSICS