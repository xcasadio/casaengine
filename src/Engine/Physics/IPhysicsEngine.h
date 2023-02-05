#pragma once

#include "CA_Export.h"
#include "IPhysicsWorld.h"

namespace CasaEngine
{
	class CA_EXPORT IPhysicsEngine
	{
	public:
		IPhysicsEngine() = default;
		virtual ~IPhysicsEngine() = default;

		virtual void Initialize() = 0;

		virtual IPhysicsWorld* CreateWorld() = 0;
	};
}
