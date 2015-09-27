
#include "Base.h"
#include "Log/LogManager.h"
#include "PhysicsEngine.h"
#include "IPhysicsWorld.h"
#include "CompilationConfig.h"

#ifdef USE_BULLET_PHYSICS
#	include "Bullet\BulletPhysicsEngine.h"
#else

#endif

#include "Memory\MemoryAllocation.h"


namespace CasaEngine
{
	SINGLETON_IMPL(PhysicsEngine)
	
	/**
	 * 
	 */
	PhysicsEngine::PhysicsEngine()
	{
		m_pPhysicsEngine = nullptr;
	}

	/**
	 * 
	 */
	PhysicsEngine::~PhysicsEngine()
	{
		if (m_pPhysicsEngine != nullptr)
		{
			DELETE_AO m_pPhysicsEngine;
		}
	}
	
	/**
	 *
	 */
	void PhysicsEngine::Initialize()
	{
		CA_ASSERT(m_pPhysicsEngine == nullptr, "Physics engine already initialized")

#ifdef USE_BULLET_PHYSICS
		m_pPhysicsEngine = NEW_AO BulletPhysicsEngine();
#else
//#	error Unknown physics engine
#endif

		//m_pPhysicsEngine->Initialize();
	}
	
	/**
	 *
	 */
	IPhysicsWorld* PhysicsEngine::CreateWorld() const
	{
		CA_ASSERT(m_pPhysicsEngine != nullptr, "Initialize the engine before call CreateWorld()")
		IPhysicsWorld *pWorld = m_pPhysicsEngine->CreateWorld();
		pWorld->SetGravity(Vector3F::Up() * -10.0f); // default
		return pWorld;
	}

	/**
	 * 
	 */
	IPhysicsEngine * PhysicsEngine::GetPhysicsEngineImpl() const
	{
		CA_ASSERT(m_pPhysicsEngine != nullptr, "Call PhysicsEngine::Initialize() before this function");
		return m_pPhysicsEngine;
	}

} // namespace CasaEngine