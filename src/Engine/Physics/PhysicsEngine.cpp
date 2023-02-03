#include "Base.h"
#include "Log/LogManager.h"
#include "PhysicsEngine.h"
#include "IPhysicsWorld.h"
#include "Bullet/BulletPhysicsEngine.h"

namespace CasaEngine
{
	PhysicsEngine::PhysicsEngine()
	{
		m_pPhysicsEngine = nullptr;
	}

	PhysicsEngine::~PhysicsEngine()
	{
		delete m_pPhysicsEngine;
	}

	void PhysicsEngine::Initialize()
	{
		CA_ASSERT(m_pPhysicsEngine == nullptr, "Physics engine already initialized")

			m_pPhysicsEngine = new BulletPhysicsEngine();
		m_pPhysicsEngine->Initialize();
	}

	IPhysicsWorld* PhysicsEngine::CreateWorld() const
	{
		CA_ASSERT(m_pPhysicsEngine != nullptr, "Initialize the engine before call CreateWorld()")
			IPhysicsWorld* pWorld = m_pPhysicsEngine->CreateWorld();
		pWorld->SetGravity(Vector3::Up() * -10.0f); // default
		return pWorld;
	}

	IPhysicsEngine* PhysicsEngine::GetPhysicsEngineImpl() const
	{
		CA_ASSERT(m_pPhysicsEngine != nullptr, "Call PhysicsEngine::Initialize() before this function");
		return m_pPhysicsEngine;
	}
}