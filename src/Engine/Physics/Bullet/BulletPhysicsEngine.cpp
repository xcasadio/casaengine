#include "Base.h"

#ifdef USE_BULLET_PHYSICS

#include "Log/LogManager.h"
#include "BulletPhysicsEngine.h"
#include "Physics/IPhysicsWorld.h"

#include "BulletCollision\BroadphaseCollision\btDbvtBroadphase.h"
#include "BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.h"
#include "BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.h"
#include "BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.h"
#include "BulletCollision/CollisionShapes/btBox2dShape.h"
#include "BulletCollision/CollisionShapes/btConvex2dShape.h"
#include "BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.h"
#include "Bullet3Common/b3Logging.h"
#include "BulletPhysicsWorld.h"


namespace CasaEngine
{
	void b3CustomPrintf (const char* msg);
	void b3CustomWarning (const char* msg);
	void b3CustomError (const char* msg);
	
	/**
	 * 
	 */
	BulletPhysicsEngine::BulletPhysicsEngine()
	{
		m_pCollisionConfig = nullptr;
		m_pDispatcher = nullptr;
		m_pOverlappingPairCache = nullptr;
		m_pConstraintSolver = nullptr;
		m_pIDebugDraw = nullptr;
	}

	/**
	 * 
	 */
	BulletPhysicsEngine::~BulletPhysicsEngine()
	{
		if (m_pCollisionConfig != nullptr)
		{
			delete m_pCollisionConfig;
		}
		
		if (m_pDispatcher != nullptr)
		{
			delete m_pDispatcher;
		}
		
		if (m_pOverlappingPairCache != nullptr)
		{
			delete m_pOverlappingPairCache;
		}
		
		if (m_pConstraintSolver != nullptr)
		{
			delete m_pConstraintSolver;
		}

		if (m_pIDebugDraw != nullptr)
		{
			delete m_pIDebugDraw;
		}
	}
	
	/**
	 *
	 */
	void BulletPhysicsEngine::Initialize()
	{
		b3SetCustomPrintfFunc(b3CustomPrintf);
		b3SetCustomWarningMessageFunc(b3CustomWarning);
		b3SetCustomErrorMessageFunc(b3CustomError);

		///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
		m_pCollisionConfig = new btDefaultCollisionConfiguration();

		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		m_pDispatcher = new	btCollisionDispatcher(m_pCollisionConfig);

		///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		m_pOverlappingPairCache = new btDbvtBroadphase();

		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		m_pConstraintSolver = new btSequentialImpulseConstraintSolver;

		//TODO : create function to activate 2D
		btVoronoiSimplexSolver* simplex = new btVoronoiSimplexSolver();
		btMinkowskiPenetrationDepthSolver* pdSolver = new btMinkowskiPenetrationDepthSolver();
		btConvex2dConvex2dAlgorithm::CreateFunc* convexAlgo2d = new btConvex2dConvex2dAlgorithm::CreateFunc(simplex,pdSolver);
		m_pDispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE,CONVEX_2D_SHAPE_PROXYTYPE, convexAlgo2d);
		m_pDispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE,CONVEX_2D_SHAPE_PROXYTYPE, convexAlgo2d);
		m_pDispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE,BOX_2D_SHAPE_PROXYTYPE, convexAlgo2d);
		m_pDispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE,BOX_2D_SHAPE_PROXYTYPE, new btBox2dBox2dCollisionAlgorithm::CreateFunc());
	}
	
	/**
	 *
	 */
	IPhysicsWorld* BulletPhysicsEngine::CreateWorld() const
	{
		CA_ASSERT(m_pCollisionConfig != nullptr 
			&& m_pDispatcher != nullptr
			&& m_pDispatcher != nullptr
			&& m_pConstraintSolver != nullptr, 
			"PhysicsEngine::CreateWorld() : Please call Initialize() before");

		BulletPhysicsWorld *pWorld = NEW_AO BulletPhysicsWorld(m_pCollisionConfig, m_pDispatcher, m_pOverlappingPairCache, m_pConstraintSolver);
		pWorld->setDebugDraw(m_pIDebugDraw);
		return pWorld;
	}

	void BulletPhysicsEngine::SetPhysicsDebugDraw(btIDebugDraw *pDebugDraw_)
	{
		m_pIDebugDraw = pDebugDraw_;
	}

	/**
	 * 
	 */
	void b3CustomPrintf (const char* msg)
	{
		CA_INFO("[BULLET] %s\n", msg);
	}

	/**
	 * 
	 */
	void b3CustomWarning (const char* msg)
	{
		CA_WARN("[BULLET] %s\n", msg);
	}

	/**
	 * 
	 */
	void b3CustomError (const char* msg)
	{
		CA_ERROR("[BULLET] %s\n", msg);
	}

}

#endif // USE_BULLET_PHYSICS
