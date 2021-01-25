#ifndef IPHYSICSENGINE_H_
#define IPHYSICSENGINE_H_

#include "CA_Export.h"
#include "IPhysicsWorld.h"

#include "Memory\MemoryAllocation.h"

namespace CasaEngine
{
	class CA_EXPORT IPhysicsEngine :
		public AllocatedObject<IPhysicsEngine>
	{
	public:
		/**
		 *
		 */
		IPhysicsEngine() {}

		/**
		 *
		 */
		virtual ~IPhysicsEngine() {}

		/**
		 *
		 */
		virtual void Initialize() = 0;

		/**
		 *
		 */
		virtual IPhysicsWorld* CreateWorld() const = 0;
	};
}

#endif // IPHYSICSENGINE_H_
