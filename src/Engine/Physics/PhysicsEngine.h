#pragma once

#include "CA_Export.h"

#include "IPhysicsWorld.h"
#include "IPhysicsEngine.h"

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
