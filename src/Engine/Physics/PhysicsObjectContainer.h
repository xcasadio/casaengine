#ifndef PHYSICSOBJECTCONTAINER_H_
#define PHYSICSOBJECTCONTAINER_H_

#include "Memory\MemoryAllocation.h"
#include "CA_Export.h"
#include "Maths\Vector3.h"
#include "Log\LogManager.h"
#include "Maths\Quaternion.h"

namespace CasaEngine
{
	/**
	 * 
	 */
	class CA_EXPORT IRigidBodyContainer :
		public AllocatedObject<IRigidBodyContainer>
	{
	public:
		virtual ~IRigidBodyContainer() {}

#if defined(CA_DEBUG)
		virtual void logInfo() = 0;
#endif // #if defined(CA_DEBUG)

		virtual const Vector3F& getLinearVelocity() const = 0;
		virtual void setLinearVelocity(const Vector3F& lin_vel) = 0;

		virtual Vector3F& getAngularVelocity() const = 0;
		virtual void setAngularVelocity(const Vector3F& ang_vel) = 0;

		virtual Vector3F& getTranslation() const = 0;
		virtual void setTranslation(const Vector3F& ang_vel) = 0;

		virtual Quaternion& getRotation() const = 0;
		virtual void setRotation(const Quaternion& rot) = 0;
	};

	/**
	 * 
	 */
	class CA_EXPORT ICollisionObjectContainer :
		public AllocatedObject<ICollisionObjectContainer>
	{
	public:
		virtual ~ICollisionObjectContainer() {}
	};

}

#endif // PHYSICSOBJECTCONTAINER_H_