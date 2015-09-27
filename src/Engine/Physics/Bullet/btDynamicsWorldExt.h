
#ifndef BTDYNAMICSWORLDEXT_H_
#define BTDYNAMICSWORLDEXT_H_

#include "CA_Export.h"

#include "BulletDynamics\Dynamics\btDynamicsWorld.h"
#include "BulletDynamics\Dynamics\btDiscreteDynamicsWorld.h"


namespace CasaEngine
{
	/**
	 * The world that contains physics entities.
	 * It is a adapter to the bullet dynamics world
	 */
	class CA_EXPORT btDynamicsWorldExt :
		public btDiscreteDynamicsWorld
	{
	public:
		btDynamicsWorldExt(btDispatcher* dispatcher, btBroadphaseInterface* broadphase, btConstraintSolver* constraintSolver, btCollisionConfiguration* collisionConfiguration);

		void debugDrawObject( const btTransform& worldTransform, const btCollisionShape* shape, const btVector3& color );
	};

} // namespace CasaEngine

#endif // BTDYNAMICSWORLDEXT_H_
