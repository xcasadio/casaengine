#include "Log/LogManager.h"
#include "BulletPhysicsEngine.h"
#include "Physics/IPhysicsWorld.h"

#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.h"
#include "BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.h"
#include "Bullet3Common/b3Logging.h"
#include "BulletPhysicsWorld.h"
#include "Game/Game.h"
#include "Tools/Bullet/BulletPhysicsDebugDrawComponent.h"

namespace CasaEngine
{
	void b3CustomPrintf(const char* msg);
	void b3CustomWarning(const char* msg);
	void b3CustomError(const char* msg);

	BulletPhysicsEngine::BulletPhysicsEngine() :
		m_pCollisionConfig(nullptr),
		m_pDispatcher(nullptr),
		m_pOverlappingPairCache(nullptr),
		m_pConstraintSolver(nullptr)
	{
	}

	BulletPhysicsEngine::~BulletPhysicsEngine()
	{
		delete m_pCollisionConfig;
		delete m_pDispatcher;
		delete m_pOverlappingPairCache;
		delete m_pConstraintSolver;
	}

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
		m_pConstraintSolver = new btSequentialImpulseConstraintSolver();
	}

	IPhysicsWorld* BulletPhysicsEngine::CreateWorld()
	{
		CA_ASSERT(m_pCollisionConfig != nullptr
			&& m_pDispatcher != nullptr
			&& m_pOverlappingPairCache != nullptr
			&& m_pConstraintSolver != nullptr,
			"PhysicsEngine::CreateWorld() : Please call Initialize() before");

		auto* pWorld = new BulletPhysicsWorld(m_pCollisionConfig, m_pDispatcher, m_pOverlappingPairCache, m_pConstraintSolver);
		auto* pDebugDraw = Game::Instance().GetGameComponent<BulletPhysicsDebugDrawComponent>();

		if (pDebugDraw != nullptr)
		{
			pWorld->setDebugDraw(pDebugDraw);
		}

		return pWorld;
	}

	void b3CustomPrintf(const char* msg)
	{
		CA_INFO("[BULLET] %s\n", msg);
	}

	void b3CustomWarning(const char* msg)
	{
		CA_WARN("[BULLET] %s\n", msg);
	}

	void b3CustomError(const char* msg)
	{
		CA_ERROR("[BULLET] %s\n", msg);
	}
}
