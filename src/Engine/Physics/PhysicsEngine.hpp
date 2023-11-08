#pragma once

#include "CA_Export.hpp"

#include  "IPhysicsWorld.hpp"
#include  "IPhysicsEngine.hpp"

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
