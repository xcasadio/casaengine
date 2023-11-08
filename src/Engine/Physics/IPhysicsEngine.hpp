#pragma once

#include "CA_Export.hpp"
#include  "IPhysicsWorld.hpp"

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
